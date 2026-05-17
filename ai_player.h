//
// Created by larix on 2026. 05. 17..
//

#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "game_master.h"

class AIPlayer {
    char my_mark;
    char opponent_mark;

    int LongestChainAt(GameMaster game, int row, int column, char mark);
    int CountInDirection(GameMaster game, int row, int column, int row_step, int column_step, char mark);
    bool WouldWin(GameMaster game, int row, int column, char mark);

public:
    AIPlayer(char my_mark = 'O');

    bool ChooseMove(GameMaster game, int& chosen_row, int& chosen_column);
};

#endif //AI_PLAYER_H