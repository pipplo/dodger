#include <allegro.h>
#include <stdlib.h>

#include "include\asteroid.h"

int score = 0;
int level = 1;
int scrolls = 0;

void asteroid_Newline() {
     int x;

     if ((scrolls % 4) == 0) {
        for (x = 0; x < level; x++) {
            screen_Array[rand() % 24][0] = 1;
        }
     }

     else {
          for (x = 0; x < 24; x++) {
              screen_Array[x][0] = 0;
          }
     }

     if (rand() % 80 == 25)
        screen_Array[rand() % 24][0] = 2;

     if ((scrolls % 500) == 0 && (scrolls > 0)) {
        level++;
        score += 50;
        //optimal_fs-=10;
     }

     if (level % 5 == 0 && level > 0) {
        level = 1;
        optimal_fs-=10;
        score += 100;
     }
     scrolls++;
     score++;
}
