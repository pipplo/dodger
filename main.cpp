#include <iostream.h>
#include <stdio.h>
#include <time.h>
#include <allegro.h>

#include "include\main.h"
#include "include\game.h"
#include "include\screen.h"
#include "include\ship.h"
#include "include\asteroid.h"
#include "include\highscores.h"
#include "collisions.h"

#include "data.h"

MIDI *music;
DATAFILE *data;
FONT *comic;

BITMAP *title;

int end_game, again;
int optimal_fs, variable_fs;
volatile int actual_fs;
int bonuses;

int main() {
       if (setup() != true)
           return 1;
       again = true;

       while (again) {
          menu();
       }

       allegro_exit();
       return 0;
}
END_OF_MAIN();

// ****** Timer Function ****** //
void timing() {
     actual_fs++;
}
END_OF_FUNCTION(timing);

// ****** Shows Opening Menu ****** //
void menu() {
    int pos = 0;
    key[KEY_ENTER] = false;
    
    blit( (BITMAP *) data[TITLE_BITMAP].dat, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit( (BITMAP *) data[SHIP_BITMAP].dat, screen, 0, 0, 405, 135 + (pos * 90), 20, 60);

    do {
        if (keypressed()) {
            if (key[KEY_DOWN]) {
                pos ++;
                key[KEY_DOWN] = false;
            }
            if (key[KEY_UP]) {
                pos--;
                key[KEY_UP] = false;
            }

            if (pos < 0)
                pos = 0;
            if (pos > 2)
                pos = 2;
            blit( (BITMAP *) data[TITLE_BITMAP].dat, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            blit( (BITMAP *) data[SHIP_BITMAP].dat, screen, 0, 0, 405, 135 + (pos * 90), 20, 60);
            readkey();
        }

    } while (!key[KEY_ENTER] && !key[KEY_ESC]);

    key[KEY_ENTER] = false;
    
    if (key[KEY_ESC])
        again = false;
    else {
        if (pos == 0)
            play();
        
        if (pos == 1)
            highscores_Show();
        
        if (pos == 2)
            info();
    }
    
}

// ****** Shows the Info Screen ****** //
void info() {
     blit( (BITMAP *) data[INFO_BITMAP].dat, screen, 0, 0, 0, 0, 640, 480);
     key[KEY_ENTER] = FALSE;
     do {
     } while(!key[KEY_ENTER]);
}

// ******    Setup Function      ****** //
// ****** Initializes Everything ****** //

bool setup() {
     // ****** Setup Random Seed ****** //
     srand(time(NULL));

     allegro_init();

     // ****** Keyboard Functions ****** //
     if( install_keyboard() < 0 ) {
         cout << "\nFatal error installing keyboard handler. There is nothing I can do, sorry :(";
         return false;
     }

     // ****** Timer Functions ****** //
     if( install_timer() < 0 ) {
         cout << "\nFatal error installing timer handler. There is nothing I can do, sorry :(";
         return false;
     }
     LOCK_VARIABLE(actual_fs);
     LOCK_FUNCTION(timing);
     install_int(timing, 1);

     // ****** Install Sound ****** //
     if ( install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) < 0) {
        cout << "Error Loading sound on this system."
                "\nI will proceed with no Sound";
        return false;
     }

     // ****** Install Graphics Drivers ****** //
     if ( set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0) {
        cout << "Error Loading Graphics into 640 x 480 mode."
                "\nCannot continue";
        return false;
     }

     // ****** Load the data file and set variables from it ****** //
     data = load_datafile("data.dat");

     // ****** System Variabes ****** //
     set_pallete((RGB *) data[MY_PALETTE].dat);
     comic = (FONT *) data[COMIC_FONT].dat;

     // ****** Sprites ****** //
     asteroid = (BITMAP *) data[AST_BITMAP].dat;
     mk_spr_mask(asteroid, 0);

     ship = (BITMAP *) data[SHIP_BITMAP].dat;
     mk_spr_mask(ship, 1);

     bonus = (BITMAP *) data[BONUS_BITMAP].dat;
     mk_spr_mask(bonus, 2);

     explode = (BITMAP *) data[EXPLODE_BITMAP].dat;

     // ****** Music ****** //
     music = (MIDI *) data[MUSIC_MIDI].dat;

     // ****** Create the bitmap for our Double Buffer ****** //
     buffer = create_bitmap(SCREEN_W, SCREEN_H);
     clear(buffer);

     // ****** Load High Scores ******
     highscores_Load();

     return true;
}

