#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

// uppgift 3
// 3. Extent the game to handle player input with arrow keys.

// Run the game for linux. using WSL (Windows machine)

//     Handle Player Input:
//         Wait for player input:
//             If Arrow Up is pressed, move the cursor up (if possible).
//             If Arrow Down is pressed, move the cursor down (if possible).
//             If Arrow Right is pressed, move the cursor right (if possible).
//             If Arrow Left is pressed, move the cursor left (if possible).
//             If Enter is pressed:
//                 If the selected cell is empty, break out of the input loop.
//                 If the selected cell is not empty, prompt the player to choose another cell.

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
public:
    Board() { resetBoard(); }

    void displayBoard(int cursorRow, int cursorCol) {
        std::cout << "\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == cursorRow && j == cursorCol) {
                    std::cout << "[" << board[i][j] << "]";
                } else {
                    std::cout << " " << board[i][j] << " ";
                }
                if (j < 2) std::cout << "|";
            }
            std::cout << "\n";
            if (i < 2) std::cout << "---+---+---\n";
        }
        std::cout << "\n";
    }

    void resetBoard() {
        char initialBoard[3][3] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
        };
        std::copy(&initialBoard[0][0], &initialBoard[0][0] + 3 * 3, &board[0][0]);
    }

    char getCell(int row, int col) const {
        return board[row][col];
    }

    void setCell(int row, int col, char value) {
        board[row][col] = value;
    }

private:
    char board[3][3];
};

class Game {
public:
    Game() : currentPlayer('X'), cursorRow(0), cursorCol(0) {}

    void play() {
        showWelcomeScreen();

        Terminal terminal;
        bool gameRunning = true;

        while (gameRunning) {
            system("clear");
            board.displayBoard(cursorRow, cursorCol);
            std::cout << "Player " << currentPlayer << ", use arrow keys to move and Enter to select a cell.\n";
            std::cout << "Press 'q' to quit.\n";
            char ch = terminal.getch();

            if (ch == '\033') {
                terminal.getch();
                char arrow = terminal.getch();
                switch (arrow) {
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
                }
            } else if (ch == '\n') { 
                if (board.getCell(cursorRow, cursorCol) != 'X' && board.getCell(cursorRow, cursorCol) != 'O') {
                    board.setCell(cursorRow, cursorCol, currentPlayer);
                    if (checkWin()) {
                        system("clear");
                        board.displayBoard(cursorRow, cursorCol);
                        std::cout << "Player " << currentPlayer << " Wins!\n";
                        gameRunning = false;
                    } else if (checkDraw()) {
                        system("clear");
                        board.displayBoard(cursorRow, cursorCol);
                        std::cout << "It's a draw!\n";
                        gameRunning = false;
                    } else {
                        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                    }
                } else {
                    std::cout << "Cell already occupied. Try again.\n";
                }
            } else if (ch == 'q') { 
                std::cout << "Game exited.\n";
                gameRunning = false;
            }
        }
    }

private:
    char currentPlayer;
    int cursorRow, cursorCol;
    Board board;

    void showWelcomeScreen() {
        system("clear");
        std::cout << "********************************\n";
        std::cout << "* Welcome to Tic-Tac-Toe Game! *\n";
        std::cout << "********************************\n";
        std::cout << "Instructions:\n";
        std::cout << "- Use arrow keys to move.\n";
        std::cout << "- Press Enter to select a cell.\n";
        std::cout << "- Press 'q' to quit at any time.\n";
        std::cout << "\nPress any key to start the game...";
        Terminal terminal;
        terminal.getch();
    }

    bool checkWin() {
        for (int i = 0; i < 3; ++i) {
            if (board.getCell(i, 0) == board.getCell(i, 1) && board.getCell(i, 1) == board.getCell(i, 2)) {
                return true;
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (board.getCell(0, i) == board.getCell(1, i) && board.getCell(1, i) == board.getCell(2, i)) {
                return true;
            }
        }
        if (board.getCell(0, 0) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 2)) {
            return true;
        }
        if (board.getCell(0, 2) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 0)) {
            return true;
        }
        return false;
    }

    bool checkDraw() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.getCell(i, j) != 'X' && board.getCell(i, j) != 'O') {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
