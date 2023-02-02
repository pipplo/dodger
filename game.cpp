#include <stdio.h>
#include <allegro.h>

#include "collisions.h"

#include "include\ship.h"
#include "include\screen.h"
#include "include\game.h"
#include "include\highscores.h"
#include "include\main.h"

// ****** Play Game Loop ******
void play() {
       // ****** Initial Variable Values ******
       //bonuses = 0;
       scrolls = 0;
       level = 1;
       end_game = false;
       
       optimal_fs = 75;
       variable_fs = 75;
       score = 0;
       
       died = false;
       // ****** Random Ship Location ******
       ship_x = rand() % 460;

       // ****** Lock timer variables and install timer ******
       actual_fs = 0;       
       // ****** Start Playing Music ******
       play_midi(music, TRUE);

       // ****** Clear the screen of asteroids ******
       for (int x = 0; x < 24; x++) {
         for (int y = 0; y < 24; y++) {
               screen_Array[x][y] = 0;
         }
       }

       // ****** Game Loop ******
       do {
          input();
          process();
          output();

          // ****** Crappy Timer based Delay Loop ******
          do {
          } while (actual_fs < variable_fs);

          actual_fs = 0;
       } while (!end_game);

        stop_midi();
       
       // ****** I died show the Score ******
       char buffer[20];
       //int score;
       //score = ((level-1) * 100) + (scrolls * 1) + (bonuses * 100);
       sprintf(buffer, "Score: %d", score);
       textout(screen, comic, buffer, 271, 191, 3);

       do {
       } while(!key[KEY_ENTER]);

       key[KEY_ENTER] = FALSE;
       
       highscores_Add(score);
}

void input() {
     if (key[KEY_LEFT])
        ship_Move(-1);
     if (key[KEY_RIGHT])
        ship_Move(1);
     if (key[KEY_ESC])
        end_game = true;

     if (key[KEY_DOWN]) {
        if ((variable_fs + 10) <= optimal_fs) {
           variable_fs += 10;
        }
        key[KEY_DOWN] = FALSE;
     }

     if (key[KEY_UP]) {
        variable_fs -= 10;
        key[KEY_UP] = FALSE;
     }
     if (key[KEY_ENTER]) {
        key[KEY_ENTER] = FALSE;
        do {
        } while(!key[KEY_ENTER]);
        key[KEY_ENTER] = FALSE;
     }
}

void process() {
     if (variable_fs > optimal_fs)
        variable_fs = optimal_fs;

     screen_Scroll();
     for (int x = 0; x < 24; x++) {
         for (int y = 18; y < 23; y++) {
             switch (screen_Array[x][y]) {
                    case 1: if (check_ppcollision(1, ship_x, ship_y, 0, (x * asteroid->w), (y - 1) * asteroid->h) != 0) {
                               end_game = true;
                               died = true;
                            }
                            break;
                    case 2: if (check_ppcollision(1, ship_x, ship_y, 2, (x * bonus->w), (y - 1) * bonus->h) != 0) {
                               score += 100;
                               screen_Array[x][y] = 0;
                            }
                            break;
             }
         }
     }
}

void output() {
     screen_Draw();
}
