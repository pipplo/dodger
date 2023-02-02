#include <allegro.h>

#include "include\ship.h"

int ship_x = 300;
int died = FALSE;

BITMAP *ship, *explode;

void ship_Move(int direction) {
    ship_x += direction * 10;
        if (ship_x > 460)
           ship_x = 460;
        if (ship_x < 0)
           ship_x = 0;
}

void ship_Draw() {
     masked_blit(ship, buffer, 0, 0, ship_x, ship_y, ship->w, ship->h);

     if (died == TRUE)
        blit(explode, buffer, 0, 0, ship_x, ship_y, ship->w, ship->h);
}

