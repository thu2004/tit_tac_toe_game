#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

class Board
{
private:
    int gameState[3][3] = {0};

public:
    Board()
    {
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

    void drawBoard(int cursor[2])
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                std::cout << ((cursor[0] == i && cursor[1] == j) ? "(" : " ") << (gameState[i][j] == 0 ? " " : 
                    (gameState[i][j] == 1 ? "X" : "O")) << ((cursor[0] == i && cursor[1] == j) ? ")" : " ");
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
    int cursor[2] = {0,0};

public:
    Game()
    {
        newGame();
        score[0] = 0, score[1] = 0;
    }

    void newGame()
    {
        board.resetBoard();
        cursor[0] = 0;
        cursor[1] = 0;
        playerTurn = -1;
    }

    int play()
    {
        bool gameRunning = true;
        while (gameRunning)
        {
            
            while (true) {
                board.clearConsole();
                std::cout << "\033[?25l";
                std::cout << "Welcome to Tic-Tac-Toe, current score is " << score[0] << " " << score[1] << std::endl;
                board.drawBoard(cursor);
                std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << ", move by using WASD, accept square with ENTER, quit with Q";
                char key = getKey();
                if (key == '\n' || key == '\r') {
                    if (board.makeMove(cursor[0], cursor[1], playerTurn)) {
                        break;
                    }
                } else if (key == 'q') {
                    std::cout << "\nPlayer " << (playerTurn == -1 ? "X" : "O") << " ended the game" << std::endl;
                    gameRunning = false;
                    return 1;
                } else {
                    moveCursor(key);
                }
            }
            switch (board.checkState()) {
                case 2:                    
                    (playerTurn == -1 ? score[0]++ : score[1]++);
                    board.clearConsole();
                    std::cout << "Welcome to Tic-Tac-Toe, current score is " << score[0] << " " << score[1] << std::endl;
                    board.drawBoard(cursor);
                    std::cout << "Player " << (playerTurn == -1 ? "X" : "O") << " has won!" << std::endl;
                    gameRunning = false;
                    break;
                case 1:
                    playerTurn = -playerTurn;
                    break;
                case 0:
                    board.clearConsole();
                    std::cout << "Welcome to Tic-Tac-Toe, current score is " << score[0] << " " << score[1] << std::endl;
                    board.drawBoard(cursor);
                    std::cout << "It's a draw" << std::endl;
                    gameRunning = false;
                    break;
            }
            
        }
        return 0;
    }

    char getKey() {
#ifdef _WIN32
        char ch = _getch();
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch) {
                case 72: return 'w'; // Up arrow
                case 80: return 's'; // Down arrow
                case 75: return 'a'; // Left arrow
                case 77: return 'd'; // Right arrow
            }
        }
        return ch;
#else
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        if (ch == 27) {
            ch = getchar();
            if (ch == 91) {
                ch = getchar();
                switch (ch) {
                    case 65: return 'w'; // Up arrow
                    case 66: return 's'; // Down arrow
                    case 68: return 'a'; // Left arrow
                    case 67: return 'd'; // Right arrow
                }
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
#endif
    }

    void moveCursor(char key) {
        switch (key) {
            case 'w':
                cursor[0] = (cursor[0] + 2) % 3;
                break;
            case 's':
                cursor[0] = (cursor[0] + 1) % 3;
                break;
            case 'a':
                cursor[1] = (cursor[1] + 2) % 3;
                break;
            case 'd':
                cursor[1] = (cursor[1] + 1) % 3;
                break;
        }
    }
};

int main() {
    Game game;
    char temp;
    while (true) {
        game.newGame();  
        if (game.play() == 1)
            break;
        std::system("pause");
    }
    return 0;

}