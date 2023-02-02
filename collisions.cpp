#include <allegro.h>
#define MAX_SPRITES 10


struct spr_mask { /* Sprite Mask */
 int bb_height; /* Bounding-box height of sprite */
 int bb_width; /* Bounding-box width of sprite */
 unsigned long int sp_mask[32]; /* The 32 entries of the 32 bit Sprite Mask */
} spr_mask[MAX_SPRITES];

void init_sp_bb() /* initialise data in Sprite mask to be zeros */
{
 int l,c;

 for (l=0; l<(MAX_SPRITES+1); l++)
 {
  spr_mask[l].bb_height=0;
  spr_mask[l].bb_width=0;
  for (c=0; c<32; c++) spr_mask[l].sp_mask[c]=0;
 }
}

void mk_spr_mask(BITMAP *s3, int spr_no)
{
 int bb_height=0; /* Bounding box height of sprite */
 int bb_width=0; /* Bounding box width of sprite */
 int x1, y1; /* Used to span through pixels within the sprite */
 int p; /* Holds return value from getpixel() */

 for (y1=0; y1<32; y1++) /* Now go through each pixel of the sprite */
 {
  for (x1=0; x1<32; x1++)       /* in turn */
  {
   p=getpixel(s3,x1,y1);         /* Find out what colour the pixel is */
   if (p>0)                     /* if the colour is non-zero */
    {
     if (y1>bb_height) bb_height=y1;  /* if > than current bounding box width, increase bounding box width */
     if (x1>bb_width) bb_width=x1;    /* if > than current bounding box heigth, increase bounding box height */
     spr_mask[spr_no].sp_mask[y1]+=0x0001<<(31-x1); /* Set corresponding bit to be 'on' in the mask*/
    }
  }
 }
 spr_mask[spr_no].bb_height=bb_height; /* Set the final bounding box height and width */
 spr_mask[spr_no].bb_width=bb_width;
}

/* this routine does normal bounding-box collision detection */

int check_bbcollision(int spr1, int spr1x, int spr1y, int spr2, int spr2x, int spr2y)
 {
 if ((spr1x>spr2x+spr_mask[spr2].bb_width) || (spr2x > spr1x+spr_mask[spr1].bb_width) ||
     (spr1y>spr2y+spr_mask[spr2].bb_height) || (spr2y> spr1y+spr_mask[spr1].bb_height))
  {
     return 0;
  }
  else
  {
   return 1;
  }
}

int check_ppcollision(int spr1, int spr1x, int spr1y, int spr2, int spr2x, int spr2y)
{
  int dx1, dx2, dy1, dy2;

 /* first do normal bounding-box collision */

 if ((spr1x>spr2x+spr_mask[spr2].bb_width) || (spr2x > spr1x+spr_mask[spr1].bb_width) ||
     (spr1y>spr2y+spr_mask[spr2].bb_height) || (spr2y> spr1y+spr_mask[spr1].bb_height))
  {
     return 0;    /* No collision */
  }
  else   /* if bounding box reports collision do pixel-perfect check*/
  {
   if (spr1x>spr2x) {
     dx1=0;            //don't need to shift sprite 1
     dx2=spr1x-spr2x;  //we need to shift sprite 2 left
   }
   else {
     dx1=spr2x-spr1x;  //we need to shift sprite 1 left
     dx2=0;            //don't need to shift sprite 2
   }
   if (spr1y>spr2y) {
     dy1=0;            //we don't need to skip any rows on sprite 1
     dy2=spr1y-spr2y;  //we need to skip this many rows on sprite 2
   }
   else {
     dy1=(spr2y-spr1y)-1;  //we need to skip this many rows on sprite 1
     dy2=0;           // we don't need to skip any rows on sprite 2
   }
   while((dy1<spr_mask[spr1].bb_height)&&(dy2<=spr_mask[spr2].bb_height)) {
     if ((spr_mask[spr1].sp_mask[dy1]<<dx1)&(spr_mask[spr2].sp_mask[dy2]<<dx2))
       return 1; /* a true collision */
     dy1++;
     dy2++;
   }
   return 0; /* no collision */
 }
}