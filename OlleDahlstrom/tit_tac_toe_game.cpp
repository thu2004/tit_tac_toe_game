#include <iostream>
#include <stdlib.h>

void displayBoard(char board[3][3]);
int getPlayerMove(char board[3][3]);
void setPlayerMark(int coordinate, char playerMark, char board[3][3]);
bool checkWin(char board[3][3]);
bool checkDraw(char board[3][3]);

int main()
{
    // empty 2d matrix
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

    // define players
    char playerX = 'X';
    char playerO = 'O';

    bool gameRunning = true;

    std::cout << "Welcome to Tic-Tac-Toe!\n";
    displayBoard(board);

    // main loop
    while (gameRunning) {
        std::cout << playerX << "'s turn.\n";
        setPlayerMark(getPlayerMove(board), playerX, board);
        displayBoard(board);
        if (checkWin(board)) {
            std::cout << "Winner: " << playerX << std::endl;
            break;
        }
        if (checkDraw(board)) {
            std::cout << "Draw!" << std::endl;
            break;
        }

        std::cout << playerO << "'s turn.\n";
        setPlayerMark(getPlayerMove(board), playerO, board);
        displayBoard(board);
        if (checkWin(board)) {
            std::cout << "Winner: " << playerO << std::endl;
            break;
        }
        if (checkDraw(board)) {
            std::cout << "Draw!" << std::endl;
            break;
        }
    }

    return 0;
}

void displayBoard(char board[3][3])
{
    system("clear");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            std::cout << board[row][col];
        }
        std::cout << std::endl;
    }
}

int getPlayerMove(char board[3][3])
{
    int coordinate;
    
    while (1) {
        std::cout << "Enter coordinate for your move (1-9): ";
        std::cin >> coordinate;
        if (coordinate > 0 && coordinate < 10) {

            int row;
            int col;

            // get row and col
            if (coordinate < 4) {
                row = 0;
                col = (coordinate - 1);
            } else if (coordinate < 7) {
                row = 1;
                col = (coordinate - 1) % 3;
            } else if (coordinate < 10) {
                row = 2;
                col = (coordinate - 1) % 6;
            }

            if (board[row][col] == ' ') {
                return coordinate;
            }
            std::cout << "Cell not empty, choose another one." << std::endl;
        } else {
            std::cout << "Out of range, choose a valid range." << std::endl;
        }
    }
}

void setPlayerMark(int coordinate, char playerMark, char board[3][3])
{
    int row;
    int col;

    if (coordinate < 4) {
        row = 0;
        col = (coordinate - 1);
    } else if (coordinate < 7) {
        row = 1;
        col = (coordinate - 1) % 3;
    } else if (coordinate < 10) {
        row = 2;
        col = (coordinate - 1) % 6;
    }

    board[row][col] = playerMark;
}

bool checkWin(char board[3][3])
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

bool checkDraw(char board[3][3])
{
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] != ' ') {
                return false;
            }
        }
    }

    return true;
}
