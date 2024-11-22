#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

class Terminal {
public:
    Terminal() {
        tcgetattr(STDIN_FILENO, &old_term);
        struct termios new_term = old_term;

        new_term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    }
    ~Terminal() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    }
    char getch() {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        return ch;
    }
private:
    struct termios old_term;
};

class Board {
private:
    vector<vector<char>> grid;

public:
    Board() : grid(3, vector<char>(3, ' ')) {}

    void print(int cursorRow, int cursorCol) const {
        cout << "\033[H\033[J";
        cout << "Tic-Tac-Toe (Use Arrow Keys):" << endl;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == cursorRow && j == cursorCol) {
                    cout << "\033[1;37;44m[ " << grid[i][j] << " ]\033[0m";
                } else {
                    if (grid[i][j] == 'X') {
                        cout << "\033[1;31m[ X ]\033[0m";
                    } else if (grid[i][j] == 'O') {
                        cout << "\033[1;32m[ O ]\033[0m";
                    } else {
                        cout << "[   ]";
                    }
                }
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "-----------------" << endl;
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
    int cursorRow = 0;
    int cursorCol = 0;
    Terminal terminal;

    void moveCursor(char arrowKey) {
        switch (arrowKey) {
            case 'A':
                if (cursorRow > 0) cursorRow--;
                break;
            case 'B':
                if (cursorRow < 2) cursorRow++;
                break;
            case 'C':
                if (cursorCol < 2) cursorCol++;
                break;
            case 'D':
                if (cursorCol > 0) cursorCol--;
                break;
            default:
                break;
        }
    }

public:
    void play() {
        bool gameRunning = true;

        while (gameRunning) {
            board.print(cursorRow, cursorCol);

            cout << "Player " << players[currentPlayer] << "'s turn." << endl;

            while (true) {
                char ch = terminal.getch();

                if (ch == '\033') {
                    char next = terminal.getch();
                    if (next == '[') {
                        char arrow = terminal.getch();
                        moveCursor(arrow);
                        board.print(cursorRow, cursorCol);
                        cout << "Player " << players[currentPlayer] << "'s turn." << endl; 
                    }
                } else if (ch == '\n') {
                    if (board.isCellEmpty(cursorRow, cursorCol)) {
                        board.placeMark(cursorRow, cursorCol, players[currentPlayer]);
                        break;
                    } else {
                        cout << "Pick another spot!" << endl;
                    }
                }
            }

            if (board.checkWin(players[currentPlayer])) {
                cout << "\033[H\033[J";
                board.print(cursorRow, cursorCol);
                cout << "Player " << players[currentPlayer] << " wins!" << endl;
                gameRunning = false;
            } else if (board.isFull()) {
                cout << "\033[H\033[J";
                board.print(cursorRow, cursorCol);
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
