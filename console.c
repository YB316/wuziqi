#include "console.h"
#include <stdio.h>

static HANDLE hInput;

void init_console()
{
    hInput = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;
    GetConsoleMode(hInput,&mode);
    SetConsoleMode(hInput,(mode | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE);

    HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info = {1,FALSE};
    SetConsoleCursorInfo(houtput,&cursor_info);

}

void draw_board(const Game *game,const ConsoleLayout *layout)
{
    HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0,0};
    SetConsoleCursorPosition(houtput,pos);

    printf("   ");
    for (int c = 0; c <BOARD_SIZE; c++)
    {
        printf("%d   ",c);
    }
    printf("\n");

    for (int r = 0;r < BOARD_SIZE;r++)
    {
        printf("   ");
        for (int c = 0;c <BOARD_SIZE;c++)
        {
            printf("+---");
        }
        printf("\n");

        printf(" %d ",r);
        for (int c = 0; c<BOARD_SIZE;c++)
        {
            printf("| %c ",game->cells[r][c]);
        }
        printf("|\n");
    }

    printf("  ");
    for (int c = 0; c < BOARD_SIZE; c++)
    {
        printf("+---");
    }
    printf("+\n");

    printf("\nCurrent Player: %c\n",game->current_player);
}

int get_mouse_click(int *out_row,int *out_col,const ConsoleLayout *layout)
{
    INPUT_RECORD rec;
    DWORD events;

    while(1)
    {
        ReadConsoleInput(hInput,&rec,1,&events);

        if (rec.EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mouse = rec.Event.MouseEvent;

            if (mouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                int mouse_x = mouse.dwMousePosition.X;
                int mouse_y = mouse.dwMousePosition.Y;

                int col = (mouse_x - layout->start_x) / layout->cell_width;
                int row = (mouse_y - layout->start_y - 1) / layout->cell_height;

                if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE )
                {
                    *out_row = row;
                    *out_col = col;
                    return 1;
                }
            }
        }
    }
}