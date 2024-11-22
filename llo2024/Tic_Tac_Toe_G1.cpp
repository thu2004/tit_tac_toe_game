#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printBoard(const vector<vector<char>>& board);
bool checkWin(const vector<vector<char>>& board, char player);
bool isBoardFull(const vector<vector<char>>& board);

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char players[] = {'X', 'O'};
    int currentPlayer = 0;
    bool gameRunning = true;

    while (gameRunning) {
        cout << string(50, '\n');
        printBoard(board);

        cout << "Player " << players[currentPlayer] << "'s turn." << endl;

        int cell;
        while (true) {
            cout << "Enter a cell number (1-9): ";
            cin >> cell;

            if (cell < 1 || cell > 9) {
                cout << "Invalid input! Choose a number between 1 and 9." << endl;
                continue;
            }

            int row = (cell - 1) / 3;
            int col = (cell - 1) % 3;

            if (board[row][col] == ' ') {
                board[row][col] = players[currentPlayer];
                break;
            } else {
                cout << "Cell is already occupied! Choose another cell." << endl;
            }
        }

        if (checkWin(board, players[currentPlayer])) {
            cout << string(50, '\n');
            printBoard(board);
            cout << "Player " << players[currentPlayer] << " wins!" << endl;
            gameRunning = false;
        } else if (isBoardFull(board)) {
            cout << string(50, '\n');
            printBoard(board);
            cout << "It's a draw!" << endl;
            gameRunning = false;
        } else {
            currentPlayer = 1 - currentPlayer;
        }
    }

    return 0;
}

void printBoard(const vector<vector<char>>& board) {
    cout << "Tic-Tac-Toe Board:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "-----------" << endl;
    }
    cout << endl;
}

bool checkWin(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;

    return false;
}

bool isBoardFull(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}
