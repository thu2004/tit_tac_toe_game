#include <iostream>
#include <string>

char board[3][3] = {{'1', '2', '3'},
                    {'4', '5', '6'},
                    {'7', '8', '9'}};

char currentPlayer = 'X';
int row, column;
int movement;

void displayBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "  " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "  \n";
        if (i < 2)
        {
            std::cout << " ---+---+---\n";
        }
    }
}

bool checkWin()
{
    for (int i = 0; i < 3; ++i) // loop 1-3
    {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) || // Row check
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer))
        {
            return true;
        }
    }
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) || // Diagonal check
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer))
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
        {
            if (board[i][j] != 'O' && board[i][j] != 'X')
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    bool gameRunning = true;
    std::cout << "Welcome to Tic-Tac-Toe!\n";

    while (gameRunning)
    {
        displayBoard();
        std::cout << "spelare: " << currentPlayer << " vart vill du placera dig? (1-9): ";
        std::cin >> movement;
        std::cout << std::endl;
        row = (movement - 1) / 3;    // omvandlar input till två variablar,
        column = (movement - 1) % 3; // minus för att kompensera att array börjar på 0
        if (board[row][column] == 'X' || board[row][column] == 'O')
        {
            std::cout << "Invalid move. Try again." << std::endl;
            continue;
        }
        for (int i = 0; i < 22; ++i) // var tvungen flytta ut denna clear screen för att annars såg man inte invalid move
            std::cout << std::endl;

        board[row][column] = currentPlayer; // placerar in i arrayen osv
        if (checkWin())
        {
            displayBoard();
            std::cout << "spelare: " << currentPlayer << " wins!" << std::endl;
            gameRunning = false;
        }
        else if (checkDraw())
        {
            displayBoard();
            std::cout << "It's a draw!" << std::endl;
            ;
            gameRunning = false;
            return 0;
        }
        if (currentPlayer == 'X') // byter spelare // måste vara efter checkwin för att annars så kollar den på fel variabel
        {
            currentPlayer = 'O';
        }
        else
        {
            currentPlayer = 'X';
        }
    }
}