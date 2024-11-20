#include <iostream>
#include <string>

class Board
{
public:
    char board[3][3] = {{'1', '2', '3'},
                        {'4', '5', '6'},
                        {'7', '8', '9'}};

    void displayBoard()
    { // printar ut ett board
        for (int i = 0; i < 3; ++i)
        {
            std::cout << "  " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "  \n";
            if (i < 2)
            {
                std::cout << " ---+---+---\n";
            }
        }
    }

    bool isPositionTaken(int row, int col)
    { // egentligen kan allt det här ligga i main
        return board[row][col] == 'X' || board[row][col] == 'O';
    }

    void placeMove(int row, int col, char player)
    {
        board[row][col] = player; // player in i rätt rowcolumn
    }

    bool checkWin(char player)
    {
        for (int i = 0; i < 3; ++i)
        {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // standard rows n columns
                (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            {
                return true;
            }
        }
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // diagonaler
            (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        {
            return true;
        }
        return false;
    }

    bool checkDraw()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            { // checkar draw
                if (board[i][j] != 'X' && board[i][j] != 'O')
                {
                    return false;
                }
            }
        }
        return true;
    }
};

class Game
{
private:
    Board board;
    char currentPlayer;

public:
    Game() : currentPlayer('X') {} // constructor

    void switchPlayer()
    {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    void clear()
    {

        // #ifdef _WIN32
        //     system("cls");
        // #else
        //     system("clear");
        // #endif

        for (int i = 0; i < 22; ++i) // clear
            std::cout << std::endl;
    }

    void play()
    {
        bool gameRunning = true;
        int position;

        std::cout << "Welcome to Tic-Tac-Toe!" << std::endl;

        while (gameRunning)
        {
            board.displayBoard();

            std::cout << "spelare " << currentPlayer << " välj position (1-9): ";
            std::cin >> position;

            if (position < 1 || position > 9)
            {
                std::cout << "fel! Skriv ett nummer mellan 1-9 :)" << std::endl;
                continue;
            }

            int row = (position - 1) / 3; // omvandlar input till två variablar,
            int col = (position - 1) % 3; // minus för att kompensera att array börjar på 0

            if (board.isPositionTaken(row, col))
            {
                std::cout << "Redan taget. Försök igen" << std::endl;
                continue;
            }

            board.placeMove(row, col, currentPlayer);

            clear();
            if (board.checkWin(currentPlayer))
            {
                board.displayBoard();
                std::cout << "spelare " << currentPlayer << " vinner!" << std::endl;
                gameRunning = false;
            }
            else if (board.checkDraw())
            {
                board.displayBoard();
                std::cout << "lika!" << std::endl;
                ;
                gameRunning = false;
            }
            switchPlayer();
        }
    }
};

int main()
{

    Game game;
    game.play();
    return 0;
}
