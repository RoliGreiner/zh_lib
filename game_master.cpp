//
// Created by larix on 2026. 05. 17..
//

#include "game_master.h"

using namespace std;

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

GameMaster::GameMaster(int board_size)
: board_size(board_size), current_player('X'), moves_made(0), state(State::Playing) {
        board.assign(board_size, vector(board_size, EMPTY_CELL));
}

void GameMaster::Reset(int new_board_size) {
    board_size = new_board_size;
    board.assign(board_size, vector(board_size, EMPTY_CELL));
    current_player = 'X';
    moves_made = 0;
    state = State::Playing;
}

bool GameMaster::IsInBounds(int row, int column) {
    return row >= 0 && row < board_size &&
           column >= 0 && column < board_size;
}

int GameMaster::CountConsecutive(int start_row, int start_column, int row_step, int column_step) {
    char player = board[start_row][start_column];
    int count = 0;

    int row = start_row + row_step;
    int column = start_column + column_step;
    while (IsInBounds(row, column) && board[row][column] == player) {
        count++;
        row += row_step;
        column += column_step;
    }
    return count;
}

bool GameMaster::IsWinningMove(int row, int column) {
    if (board[row][column] == EMPTY_CELL)
        return false;

    for (auto direction : DIRECTIONS) {
        int total = 1
            + CountConsecutive(row, column, direction.row_step, direction.column_step)
            + CountConsecutive(row, column, -direction.row_step, -direction.column_step);
        if (total >= WIN_LENGTH)
            return true;
    }
    return false;
}

void GameMaster::SwitchPlayer() {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

void GameMaster::UpdateStateAfterMove(int last_row, int last_column) {
    if (IsWinningMove(last_row, last_column)) {
        state = (current_player == 'X') ? State::XWon : State::OWon;
    } else if (moves_made == board_size * board_size) {
        state = State::Draw;
    } else {
        SwitchPlayer();
    }
}

bool GameMaster::TryMove(int row, int column) {
    if (state != State::Playing)
        return false;
    if (!IsInBounds(row, column))
        return false;
    if (board[row][column] != EMPTY_CELL)
        return false;

    board[row][column] = current_player;
    moves_made++;
    UpdateStateAfterMove(row, column);
    return true;
}