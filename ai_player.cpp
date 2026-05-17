//
// Created by larix on 2026. 05. 17..
//

#include "ai_player.h"

namespace {
    struct Direction {
        int row_step;
        int column_step;
    };

    const Direction DIRECTIONS[] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1},
    };
}

AIPlayer::AIPlayer(char my_mark)
: my_mark(my_mark), opponent_mark(my_mark == 'X' ? 'O' : 'X') {
}

int AIPlayer::CountInDirection(GameMaster game, int row, int column, int row_step, int column_step, char mark) {
    int count = 0;
    int size = game.Size();
    int current_row = row + row_step;
    int current_column = column + column_step;

    while (current_row >= 0 && current_row < size &&
           current_column >= 0 && current_column < size &&
           game.At(current_row, current_column) == mark) {
        count++;
        current_row += row_step;
        current_column += column_step;
    }
    return count;
}

int AIPlayer::LongestChainAt(GameMaster game, int row, int column, char mark) {
    int longest = 0;
    for (auto direction : DIRECTIONS) {
        int before = CountInDirection(game, row, column, -direction.row_step, -direction.column_step, mark);
        int after = CountInDirection(game, row, column, direction.row_step, direction.column_step, mark);
        int total = 1 + before + after;
        if (total > longest) {
            longest = total;
        }
    }
    return longest;
}

bool AIPlayer::WouldWin(GameMaster game, int row, int column, char mark) {
    return LongestChainAt(game, row, column, mark) >= GameMaster::WIN_LENGTH;
}

bool AIPlayer::ChooseMove(GameMaster game, int& chosen_row, int& chosen_column) {
    int size = game.Size();

    bool board_is_empty = true;
    for (int row = 0; row < size && board_is_empty; row++) {
        for (int column = 0; column < size && board_is_empty; column++) {
            if (game.At(row, column) != GameMaster::EMPTY_CELL) {
                board_is_empty = false;
            }
        }
    }
    if (board_is_empty) {
        chosen_row = size / 2;
        chosen_column = size / 2;
        return true;
    }

    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            if (game.At(row, column) != GameMaster::EMPTY_CELL)
                continue;
            if (WouldWin(game, row, column, my_mark)) {
                chosen_row = row;
                chosen_column = column;
                return true;
            }
        }
    }

    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            if (game.At(row, column) != GameMaster::EMPTY_CELL)
                continue;
            if (WouldWin(game, row, column, opponent_mark)) {
                chosen_row = row;
                chosen_column = column;
                return true;
            }
        }
    }

    int best_chain_length = -1;
    int best_row = -1;
    int best_column = -1;
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            if (game.At(row, column) != GameMaster::EMPTY_CELL)
                continue;

            int my_chain = LongestChainAt(game, row, column, my_mark);
            int opponent_chain = LongestChainAt(game, row, column, opponent_mark);
            int effective_chain = my_chain > opponent_chain ? my_chain : opponent_chain;

            if (effective_chain > best_chain_length) {
                best_chain_length = effective_chain;
                best_row = row;
                best_column = column;
            }
        }
    }

    if (best_row >= 0) {
        chosen_row = best_row;
        chosen_column = best_column;
        return true;
    }

    return false;
}