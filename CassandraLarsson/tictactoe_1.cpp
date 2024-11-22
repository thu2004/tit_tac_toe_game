#include <iostream>
#include <cstdlib>

#/* ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void clearConsole() {
#ifdef _WIN32
    std::system("CLS");
#else
    std::system("clear");
#endif
} */

void clearConsole() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear the screen and move the cursor to the top-left corner
}

void printBoard(int gameState[3][3]) {
    clearConsole();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << " " << (gameState[i][j] == 0 ? " " : (gameState[i][j] == 1 ? "X" : "O")) << " ";
            if (j != 2)
                std::cout << "|";
            else
                std::cout << std::endl;
        }
        if (i !=2 )
            std::cout << "---|---|---\n";
        else
            std::cout << std::endl;
    }
}

bool playerInput(int gameState[3][3], int playerTurn) {
    int x,y;
    while (true) {
        std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << ", enter your move (row and column): ";        
        std::cin >> x >> y;

        if (x == 9 && y == 9) {
            std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << " ended the game" << std::endl;
            return false;
        }

        --x; --y;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && gameState[x][y] == 0) {
            gameState[x][y] = (playerTurn == -1 ? 1 : 2); // 1 for X, 2 for O
            return true;
        } else {
            std::cout << "Invalid move. Please try again." << std::endl;
        }
    }    
}

bool checkState(int gameState[3][3], int playerTurn) {
    // Check rows for a win
    for (int i = 0; i < 3; ++i) {
        if (gameState[i][0] == gameState[i][1] && gameState[i][1] == gameState[i][2] && gameState[i][0] != 0) {
            printBoard(gameState);
            std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << " has won!" << std::endl;
            return false;
        }
    }

    // Check columns for a win
    for (int i = 0; i < 3; ++i) {
        if (gameState[0][i] == gameState[1][i] && gameState[1][i] == gameState[2][i] && gameState[0][i] != 0) {
            printBoard(gameState);
            std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << " has won!" << std::endl;
            return false;
        }
    }

    // Check diagonals for a win
    if (gameState[0][0] == gameState[1][1] && gameState[1][1] == gameState[2][2] && gameState[0][0] != 0) {
        printBoard(gameState);
        std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << " has won!" << std::endl;
        return false;
    }
    if (gameState[0][2] == gameState[1][1] && gameState[1][1] == gameState[2][0] && gameState[0][2] != 0) {
        printBoard(gameState);
        std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << " has won!" << std::endl;
        return false;
    }

    // Check for a draw
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (gameState[i][j] == 0) {
                return true; // Continue the game
            }
        }
    }

    std::cout << "It's a draw" << std::endl;
    return false; // Game over
}

int main() {
    bool gameRunning = true;
    int gameState[3][3] = {0};
    int playerTurn = -1; // -1 = x, 1 = O

    std::cout << "Welcome to tic-tac-toe!\n\n";

    while (gameRunning) {
        printBoard(gameState);
        gameRunning = playerInput(gameState, playerTurn);
        if (!gameRunning) { break;}
        gameRunning = checkState(gameState, playerTurn);
        playerTurn = -playerTurn;
    }

    return 0;
}