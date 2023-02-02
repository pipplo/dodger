extern int score;
extern int end_game;
extern int ship_x, died;
extern int optimal_fs, variable_fs;
extern volatile int actual_fs;
extern int screen_Array[24][24];

extern BITMAP *ship, *asteroid, *buffer, *bonus, *explode;
extern MIDI *music;

void input();
void play();
void process();
void output();
