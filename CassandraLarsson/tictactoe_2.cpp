#include <iostream>

class Board
{
private:
    int gameState[3][3];

public:
    Board()
    {
        resetBoard();
    }

    void resetBoard()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                gameState[i][j] = 0;
            }
        }
    }

    bool makeMove(int x, int y, int player)
    {
        --x;
        --y;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && gameState[x][y] == 0)
        {
            gameState[x][y] = (player == -1 ? 1 : 2); // 1 for X, 2 for O
            return true;
        }
        else
        {
            return false;
        }
    }

    void drawBoard()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                std::cout << " " << (gameState[i][j] == 0 ? " " : (gameState[i][j] == 1 ? "X" : "O")) << " ";
                if (j != 2)
                    std::cout << "|";
                else
                    std::cout << std::endl;
            }
            if (i != 2)
                std::cout << "---|---|---\n";
            else
                std::cout << std::endl;
        }
    }

    int checkState()
    {
        // Check rows for a win
        for (int i = 0; i < 3; ++i)
        {
            if (gameState[i][0] == gameState[i][1] && gameState[i][1] == gameState[i][2] && gameState[i][0] != 0)
            {
                return 2;
            }
        }

        // Check columns for a win
        for (int i = 0; i < 3; ++i)
        {
            if (gameState[0][i] == gameState[1][i] && gameState[1][i] == gameState[2][i] && gameState[0][i] != 0)
            {
                return 2;
            }
        }

        // Check diagonals for a win
        if (gameState[0][0] == gameState[1][1] && gameState[1][1] == gameState[2][2] && gameState[0][0] != 0)
        {
            return 2;
        }
        if (gameState[0][2] == gameState[1][1] && gameState[1][1] == gameState[2][0] && gameState[0][2] != 0)
        {
            return 2;
        }

        // Check for a draw
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (gameState[i][j] == 0)
                {
                    return 1; // Continue the game
                }
            }
        }

        return 0; // Game over
    }    

    void clearConsole()
    {
        std::cout << "\033[2J\033[1;1H";
    }
};

class Game
{
private:
    Board board;
    int playerTurn;
    int score[2];

public:
    Game()
    {
        newGame();
        score[0] = 0, score[1] = 0;
    }

    void newGame()
    {
        board.resetBoard();
        playerTurn = -1;
    }

    void play()
    {
        bool gameRunning = true;
        while (gameRunning)
        {
            board.clearConsole();
            std::cout << "Welcome to Tic-Tac-Toe, current score is " << score[0] << " " << score[1] << std::endl;
            board.drawBoard();
            int x, y;
            while (true)
            {
                std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << ", enter your move (row and column): ";
                std::cin >> x >> y;

                if (x == 9 && y == 9)
                {
                    std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << " ended the game" << std::endl;
                    gameRunning = false;
                    break;
                }
                if (board.makeMove(x, y, playerTurn)) {
                    break;
                }
                else
                    std::cout << "Illegal move, please try again" << std::endl;
            }
            switch (board.checkState()) {
                case 2:                    
                    (playerTurn == -1 ? score[0]++ : score[1]++);
                    board.clearConsole();
                    std::cout << "Welcome to Tic-Tac-Toe, current score is " << score[0] << " " << score[1] << std::endl;
                    board.drawBoard();
                    std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << " has won!" << std::endl;
                    gameRunning = false;
                    break;
                case 1:
                    playerTurn = -playerTurn;
                    break;
                case 0:
                    board.clearConsole();
                    std::cout << "Welcome to Tic-Tac-Toe, current score is " << score[0] << " " << score[1] << std::endl;
                    board.drawBoard();
                    std::cout << "It's a draw" << std::endl;
                    gameRunning = false;
                    break;
            }
        }
    }
};

int main() {
    Game game;
    char temp;
    while (true) {
        game.newGame();      
        game.play();
        std::system("pause");
    }
    return 0;

}