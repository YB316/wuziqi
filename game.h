#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 9             //棋盘大小 9*9
#define WIN_LENGTH 5             //获胜需要连城的棋子数 （5子）
#define EMPTY_CELL '.'           //空格子用'.'填充

typedef enum                     //枚举游戏状态
{
    GAME_RUNNING,                //游戏进行中
    GAME_X_WINS,                 //X获胜
    GAME_O_WINS,                 //O获胜
    GAME_DRAW                    //平局
} GameStatus;

typedef enum                     //枚举落子结果
{
    MOVE_ACCEPTED,               //落子有效
    MOVE_OUT_OF_BOUNDS,          //落子超出棋盘
    MOVE_OCCUPIED                //格子已被占领
}MoveResult;

typedef struct                   //实时游戏状态
{
    char cells[BOARD_SIZE][BOARD_SIZE];  //棋盘二维数组，存'X','O','.'
    char current_player;         //当前该谁下棋
    int move_count;             //已落子数，判断是否平局
    GameStatus status;
}Game;
//    游戏逻辑声明（具体操作在game.c）
void init_game(Game *game);      //初始化游戏

MoveResult make_move(Game *game,int row,int col);//执行落子操作

void check_game_status(Game *game,int row,int col);//检查游戏状态

#endif