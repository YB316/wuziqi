#include <stdio.h>
#include "game.h"
#include "console.h"

int main()
{
    Game game;

    ConsoleLayout layout = {4,2,4,2};
    
    init_game(&game);

    init_console();

    while (game.status == GAME_RUNNING)
    {
        draw_board(&game,&layout);

        printf("Player %c click mouse to move…\n",game.current_player);

        int row,col;
        if (get_mouse_click(&row,&col,&layout))
        {
            MoveResult result = make_move(&game,row,col);

            if (result == MOVE_OCCUPIED)
            {
                printf("❌ Occupied! Choose another cell.\n");
            }else if(result == MOVE_OUT_OF_BOUNDS){
                printf("❌ Out of bounds!Click inside the board.\n");
            }
        }      
    }

    draw_board(&game,&layout);

    if (game.status == GAME_X_WINS)
    {
        printf("Player X wins!\n");
    } else if (game.status == GAME_O_WINS)
    {
        printf("Player O wins!\n");
    } else if (game.status == GAME_DRAW)
    {
        printf("It is a draw!Board is full.\n");
    }

    printf("\nPress Enter to exit…");
    getchar();

    return 0;
}