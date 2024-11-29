#include <iostream>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

class Terminal
{
    private:
        struct termios old_term;
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

        char getch();
};

char Terminal::getch()
{
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}


class Game
{
    private:
        char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    public:
        void displayBoard(int cursor_row = -1, int cursor_col = -1, char playerMark = ' ');
        bool checkWin();
        bool checkDraw();
        void setMark(char playerMark);
        void handleArrowKeys(int *row, int *col, char playerMark);
};

void Game::handleArrowKeys(int *row, int *col, char playerMark)
{
    Terminal terminal;
    int cursor_row = 1;
    int cursor_col = 1;
    displayBoard(cursor_row, cursor_col, playerMark);

    while (true) {
        char ch = terminal.getch();
        if (ch == '\033') {
            char next = terminal.getch();
            if (next == '[') {
                char arrow = terminal.getch();
                switch (arrow) {
                    case 'A':
                        if (cursor_row > 0) {
                            cursor_row -= 1;
                        }
                        break;
                    case 'B':
                        if (cursor_row < 2) {
                            cursor_row += 1;
                        }
                        break;
                    case 'C':
                        if (cursor_col < 2) {
                            cursor_col += 1;
                        }
                        break;
                    case 'D':
                        if (cursor_col > 0) {
                            cursor_col -= 1;
                        }
                        break;
                    default:
                        break;
                }
                displayBoard(cursor_row, cursor_col, playerMark);
            }
        } else {
            if (ch == '\n') {
                if (this->board[cursor_row][cursor_col] == ' ') {
                    *row = cursor_row;
                    *col = cursor_col;
                    break;
                } else {
                    std::cout << "Cell not empty, choose another one.\n";
                }
            }
        }
    }
}

void Game::displayBoard(int cursor_row, int cursor_col, char playerMark)
{
    system("clear");
    std::cout << "+---+---+---+\n";
    for (int row = 0; row < 3; row++) {
        std::cout << "|";
        for (int col = 0; col < 3; col++) {
            if (cursor_row == row && cursor_col == col) {
                std::cout << ">" << this->board[row][col] << "<|";
            } else {
                std::cout << " " << this->board[row][col] << " |";
            }
        }
        std::cout << "\n";
        std::cout << "+---+---+---+\n";
    }
    if (playerMark != ' ') {
        std::cout << playerMark << "'s turn." << std::endl;
    }
}

bool Game::checkWin()
{
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] != ' ' &&
             board[i][0] == board[i][1] &&
             board[i][1] == board[i][2]) ||
            (board[0][i] != ' ' &&
             board[0][i] == board[1][i] &&
             board[1][i] == board[2][i])) {
            return true;
        }
    }

    if (board[0][0] != ' ' &&
            board[0][0] == board[1][1] &&
            board[1][1] == board[2][2]) {
        return true;
    }

    if (board[0][2] != ' ' &&
            board[0][2] == board[1][1] &&
            board[1][1] == board[2][0]) {
        return true;
    }

    return false;
}

bool Game::checkDraw()
{
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (this->board[row][col] != ' ') {
                return false;
            }
        }
    }

    return true;
}

void Game::setMark(char playerMark)
{
    int row;
    int col;
    handleArrowKeys(&row, &col, playerMark);
    this->board[row][col] = playerMark;
}

class Player
{
    private:
        char playerMark;
    public:
        Player(char playerMark) : playerMark(playerMark) {}
        char getPlayerMark();
};

char Player::getPlayerMark()
{
    return this->playerMark;
}

int main()
{
    Game game;
    Player playerX('X');
    Player playerO('O');

    bool gameRunning = true;

    std::cout << "Welcome to Tic-Tac-Toe!\n";
    game.displayBoard();

    while (gameRunning) {
        std::cout << playerX.getPlayerMark() << "'s turn.\n";
        game.setMark(playerX.getPlayerMark());
        game.displayBoard();

        if (game.checkWin()) {
            std::cout << "Winner: " << playerX.getPlayerMark() << std::endl;
            break;
        }
        if (game.checkDraw()) {
            std::cout << "Draw!" << std::endl;
            break;
        }

        std::cout << playerO.getPlayerMark() << "'s turn.\n";
        game.setMark(playerO.getPlayerMark());
        game.displayBoard();

        if (game.checkWin()) {
            std::cout << "Winner: " << playerO.getPlayerMark() << std::endl;
            break;
        }
        if (game.checkDraw()) {
            std::cout << "Draw!" << std::endl;
            break;
        }

    }

    return 0;
}
