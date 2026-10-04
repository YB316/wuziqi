#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>
#include "game.h"

typedef struct {
    int start_x;
    int start_y;
    int cell_width;
    int cell_height;
} ConsoleLayout;

void init_console();

void draw_board(const Game *game,const ConsoleLayout *layout);

int get_mouse_click(int *out_row,int *out_col,const ConsoleLayout *layout);

#endif