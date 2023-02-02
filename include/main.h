extern int num_bullets, bullets_available;
extern int level, scrolls;
extern int end_game;
extern int ship_x;

extern BITMAP *ship, *asteroid, *buffer, *bonus, *explode;

int main();
bool setup();
void timing(...);
void info();
void menu();
