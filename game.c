#include "game.h"

void init_game(Game *game)
{
    for(int r = 0;r < BOARD_SIZE;r++)
    {
        for(int c = 0;c < BOARD_SIZE;c++)
        {
            game->cells[r][c] = EMPTY_CELL;
        }
    }
    game->current_player = 'X';
    game->move_count = 0;
    game->status = GAME_RUNNING;
}

MoveResult make_move(Game *game,int row,int col)
{
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
    {
        return MOVE_OUT_OF_BOUNDS;
    }
    if (game->cells[row][col] != EMPTY_CELL)
    {
        return MOVE_OCCUPIED;
    }

    game->cells[row][col] = game->current_player;
    game->move_count++;

    check_game_status(game,row,col);

    if (game->status == GAME_RUNNING)
    {
        if (game->current_player == 'X')
        {
            game->current_player == 'O';
        } else {
            game->current_player == 'X';
        }
    }

    return MOVE_ACCEPTED;
}

void check_game_status(Game *game,int row,int col)
{
    char player = game->cells[row][col];

    int dx[4] = {0,1,1,1};
    int dy[4] = {1,0,1,-1};

    for (int i = 0;i < 4;i++)
    {
        int count = 1;

        for (int step = 1;step < WIN_LENGTH;step++)
        {
            int nx = row + dx[i] * step;
            int ny = col + dy[i] * step;

            if(nx < 0 ||nx >=BOARD_SIZE || ny < 0 || ny >=BOARD_SIZE || game->cells[nx][ny] != player)
            {
                break;
            }

            count++;
        }
        
        for (int step = 1;step < WIN_LENGTH;step++)
        {
            int nx = row - dx[i] * step;
            int ny = col - dy[i] * step;

            if(nx < 0 ||nx >=BOARD_SIZE || ny < 0 || ny >=BOARD_SIZE || game->cells[nx][ny] != player)
            {
                break;
            }

            count++;
        }

        if (count >= WIN_LENGTH)
        {
            if(player =='X')
            {
                game->status = GAME_X_WINS;
            }else {
                game->status = GAME_O_WINS;
            }
            return;
        }
    }

    if(game->move_count == BOARD_SIZE * BOARD_SIZE)
    {
        game->status = GAME_DRAW;
    }
}