//
// Created by larix on 2026. 05. 17..
//

#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include <vector>

using namespace std;

class GameMaster {
public:
    enum class State {
        Playing,
        XWon,
        OWon,
        Draw
    };

    static constexpr char EMPTY_CELL = ' ';
    static constexpr int WIN_LENGTH = 5;

private:
    int board_size;
    vector<vector<char>> board;
    char current_player;
    int moves_made;
    State state;

    bool IsWinningMove(int row, int column);
    int CountConsecutive(int start_row, int start_column, int row_step, int column_step);
    void SwitchPlayer();
    void UpdateStateAfterMove(int last_row, int last_column);
    bool IsInBounds(int row, int column);

public:
    GameMaster(int board_size = 15);

    void Reset(int new_board_size);

    int Size() const { return board_size; }
    char At(int row, int column) const { return board[row][column]; }
    char CurrentPlayer() const { return current_player; }
    State GetState() const { return state; }
    bool TryMove(int row, int column);
};

#endif //GAME_MASTER_H