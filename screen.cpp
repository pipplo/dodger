#include <allegro.h>
#include <stdio.h>

#include "include\screen.h"
#include "include\ship.h"
#include "include\asteroid.h"

int screen_Array[24][24];

BITMAP *buffer, *asteroid, *bonus;

void screen_Scroll() {
     int x, y;
     for (y = 23; y > 0; y--) {
         for (x = 0; x < 24; x++) {
             screen_Array[x][y] = screen_Array[x][y - 1];
             screen_Array[x][y - 1] = 0;
             }
     }
     asteroid_Newline();
}

void screen_Draw() {
     clear(buffer);
     int x, y;
     for (y = 0; y < 24; y++) {
         for (x = 0; x < 24; x++) {
             switch (screen_Array[x][y]) {
                    case 1: blit(asteroid, buffer, 0, 0, (x * asteroid->w), (y * asteroid->h), asteroid->w, asteroid->h);
                            break;
                    case 2: blit(bonus, buffer, 0, 0, (x * bonus->w), ( y * bonus->h), bonus->w, bonus->h);
                            break;
             }
         }
     }
     ship_Draw();

     screen_Info();
     screen_Show();
}

void screen_Info() {

     char score_Buffer[20];
     line(buffer, 482, 0, 482, 480, level);
     //score = ((level-1) * 100) + (scrolls * 1) + (bonuses * 100);
     sprintf(score_Buffer, "Score: %d", score);
     textout(buffer, comic, score_Buffer, 484, 10, level);
     sprintf(score_Buffer, "Level: %d", level);
     textout(buffer, comic, score_Buffer, 484, 40, level);

}

void screen_Show() {
     blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


