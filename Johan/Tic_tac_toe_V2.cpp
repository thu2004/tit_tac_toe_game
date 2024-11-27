#include <iostream>


// uppgift 2
// 2. Refactory the game using Object Oriented Programming.
// Create Game and Board class and define the attributes and methods.
// Rewrite the main function.

class Board
{
public:
    Board() { resetBoard(); }

    void displayBoard()
    {
        for (int i = 0; i < 3; ++i)
        {
            std::cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << std::endl;
            if (i < 2)
            {
                std::cout << "---+---+---\n";
            }
        }
    }

    void resetBoard()
    {
        char initialBoard[3][3] = {{'1', '2', '3'},
                                   {'4', '5', '6'},
                                   {'7', '8', '9'}};
        std::copy(&initialBoard[0][0], &initialBoard[0][0] + 3 * 3, &board[0][0]);
    }

    char getCell(int row, int col) const
    {
        return board[row][col];
    }

    void setCell(int row, int col, char value)
    {
        board[row][col] = value;
    }

private:
    char board[3][3];
};

class Game
{
public:
    Game() : currentPlayer('X') {}

    void play()
    {
        bool gameRunning = true;
        std::cout << "Welcome to Tic-Tac-Toe!\n";

        while (gameRunning)
        {
            system("clear");
            board.displayBoard();
            std::cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            std::cin >> choice;
            makeMove(choice);
            if (checkWin())
            {
                board.displayBoard();
                std::cout << "Player " << currentPlayer << " Wins!" << std::endl;
                gameRunning = false;
            }
            else if (checkDraw())
            {
                board.displayBoard();
                std::cout << "It's a draw!" << std::endl;
                gameRunning = false;
            }
            else
            {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
    }

private:
    char currentPlayer;
    int choice;
    Board board;

    bool checkWin()
    {
        // Check rows
        for (int i = 0; i < 3; ++i)
        {
            if (board.getCell(i, 0) == board.getCell(i, 1) && board.getCell(i, 1) == board.getCell(i, 2))
            {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; ++i)
        {
            if (board.getCell(0, i) == board.getCell(1, i) && board.getCell(1, i) == board.getCell(2, i))
            {
                return true;
            }
        }

        // Check diagonals
        if (board.getCell(0, 0) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 2))
        {
            return true;
        }
        if (board.getCell(0, 2) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 0))
        {
            return true;
        }

        return false;
    }

    bool checkDraw()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board.getCell(i, j) != 'X' && board.getCell(i, j) != 'O')
                    return false;
            }
        }
        return true;
    }

    void makeMove(int choice)
    {
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if (board.getCell(row, col) != 'X' && board.getCell(row, col) != 'O')
        {
            board.setCell(row, col, currentPlayer);
        }
        else
        {
            system("clear");
            std::cout << "Invalid move! Try again.\n";
            board.displayBoard();
            std::cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            std::cin >> choice;
            makeMove(choice);
        }
    }
};

int main()
{
    Game game;
    game.play();
    return 0;
}
