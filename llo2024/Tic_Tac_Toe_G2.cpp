#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Board {
private:
    vector<vector<char>> grid;

public:
    Board() : grid(3, vector<char>(3, ' ')) {}

    void print() const {
        cout << "Tic-Tac-Toe Board:" << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << " " << grid[i][j] << " ";
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "-----------" << endl;
        }
        cout << endl;
    }

    bool isCellEmpty(int row, int col) const {
        return grid[row][col] == ' ';
    }

    void placeMark(int row, int col, char mark) {
        grid[row][col] = mark;
    }

    bool checkWin(char player) const {
        for (int i = 0; i < 3; ++i) {
            if ((grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) ||
                (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player)) {
                return true;
            }
        }
        if ((grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) ||
            (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player)) {
            return true;
        }
        return false;
    }

    bool isFull() const {
        for (const auto& row : grid) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }
};

class Game {
private:
    Board board;
    char players[2] = {'X', 'O'};
    int currentPlayer = 0;

    pair<int, int> inputToCell(int input) const {
        return {(input - 1) / 3, (input - 1) % 3};
    }

public:
    void play() {
        bool gameRunning = true;

        while (gameRunning) {
            cout << string(50, '\n');
            board.print();

            cout << "Player " << players[currentPlayer] << "'s turn." << endl;

            int cell;
            while (true) {
                cout << "Enter a cell number (1-9): ";
                cin >> cell;

                if (cell < 1 || cell > 9) {
                    cout << "Invalid input! Choose a number between 1 and 9." << endl;
                    continue;
                }

                auto [row, col] = inputToCell(cell);

                if (board.isCellEmpty(row, col)) {
                    board.placeMark(row, col, players[currentPlayer]);
                    break;
                } else {
                    cout << "Cell is already occupied! Choose another cell." << endl;
                }
            }

            if (board.checkWin(players[currentPlayer])) {
                cout << string(50, '\n');
                board.print();
                cout << "Player " << players[currentPlayer] << " wins!" << endl;
                gameRunning = false;
            } else if (board.isFull()) {
                cout << string(50, '\n');
                board.print();
                cout << "It's a draw!" << endl;
                gameRunning = false;
            } else {
                currentPlayer = 1 - currentPlayer;
            }
        }
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
