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

        printf("请玩家 %c 点击鼠标左键落子…\n",game.current_player);

        int row,col;
        if (get_mouse_click(&row,&col,&layout))
        {
            MoveResult result = make_move(&game,row,col);

            if (result == MOVE_OCCUPIED)
            {
                printf("❌ 此处已经落子，请重新选择!\n");
            }else if(result == MOVE_OUT_OF_BOUNDS){
                printf("❌ 超出棋盘范围，请重新选择!\n");
            }
        }      
    }

    draw_board(&game,&layout);

    if (game.status == GAME_X_WINS)
    {
        printf("玩家 X 获胜!\n");
    } else if (game.status == GAME_O_WINS)
    {
        printf("玩家 O 获胜!\n");
    } else if (game.status == GAME_DRAW)
    {
        printf("平局!棋盘已满。\n");
    }

    printf("\n按回车键退出…");
    getchar();

    return 0;
}