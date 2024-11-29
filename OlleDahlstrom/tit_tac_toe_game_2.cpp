#include <iostream>
#include <stdlib.h>

class Game
{
    private:
        char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    public:
        void displayBoard();
        bool checkWin();
        bool checkDraw();
        void setMark(int coordinate, char playerMark);
        bool isEmpty(int coordinate);
};

void Game::displayBoard()
{
    system("clear");
    std::cout << "+---+---+---+\n";
    for (int row = 0; row < 3; row++) {
        std::cout << "|";
        for (int col = 0; col < 3; col++) {
            std::cout << " " << this->board[row][col] << " |";
        }
        std::cout << "\n";
        std::cout << "+---+---+---+\n";
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

void Game::setMark(int coordinate, char playerMark)
{
    int row;
    int col;

    if (coordinate < 4) {
        row = 0;
        col = (coordinate - 1);
    } else if (coordinate < 7) {
        row = 1;
        col = (coordinate - 1) % 3;
    } else {
        row = 2;
        col = (coordinate - 1) % 6;
    }

    this->board[row][col] = playerMark;
}

bool Game::isEmpty(int coordinate) {
    int row;
    int col;

    if (coordinate < 4) {
        row = 0;
        col = (coordinate - 1);
    } else if (coordinate < 7) {
        row = 1;
        col = (coordinate - 1) % 3;
    } else {
        row = 2;
        col = (coordinate - 1) % 6;
    }

    if (this->board[row][col] == ' ') {
        return true;
    }
    return false;
}

class Player
{
    private:
        char playerMark;
    public:
        Player(char playerMark) : playerMark(playerMark) {}
        char getPlayerMark();
        int getMove(Game game);
};

char Player::getPlayerMark()
{
    return this->playerMark;
}

int Player::getMove(Game game)
{
    int coordinate;

    while (1) {
        std::cout << "Enter coordinate for your move: (1-9): ";
        std::cin >> coordinate;

        if (coordinate > 0 && coordinate < 10) {

            if (game.isEmpty(coordinate)) {
                return coordinate;
            }

            std::cout << "Cell not empty, choose another one.\n";
        } else {
            std::cout << "Out of range, choose a valid range.\n";
        }
    }
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
        game.setMark(playerX.getMove(game), playerX.getPlayerMark());
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
        game.setMark(playerO.getMove(game), playerO.getPlayerMark());
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
