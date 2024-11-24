#include <iostream>
//uppgift 1
//1. Create a Tic-Tac-Toe game run in a console

char board[3][3] = {{'1', '2', '3'},
                    {'4', '5', '6'},
                    {'7', '8', '9'}};

char currentPlayer = 'X';
int choice;

// Function declarations
void displayBoard();
bool checkWin();
bool checkDraw();
void makeMove(int choice);

int main()
{
    bool gameRunning = true;
    std::cout << "Welcome to Tic-Tac-Toe!\n";

    while (gameRunning)
    {
        system("clear");
        displayBoard();
        std::cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        std::cin >> choice;
        makeMove(choice);
        if (checkWin())
        {
            displayBoard();
            std::cout << "Player " << currentPlayer << " Wins!" << std::endl;
            break;
        }
        if (checkDraw())
        {
            displayBoard();
            std::cout << "It's a draw!" << std::endl;
            break;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

// Function to display the game board
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

// Function to check if a player has won
bool checkWin()
{
    // Check rows
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return true;
    }

    return false;
}

// Function to check if the game is a draw
bool checkDraw()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }
    return true;
}

// Function to make a move
void makeMove(int choice)
{
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O')
    {
        board[row][col] = currentPlayer;
    }
    else
    {
        system("clear");
        std::cout << "Invalid move! Try again.\n";
        displayBoard();
        std::cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        std::cin >> choice;
        makeMove(choice);
    }
}
