#include <iostream>
#include <string>

using namespace std;

class TicTacToe 
{
private:
    char board[3][3];
    string player1, player2;
    char currentMarker;
    int currentPlayer;
    int moves;

    void displayBoard() const 
    {
        cout << " ______________________________________\n";
        for (int i = 0; i < 3; ++i) 
        {
            cout << "|            |            |            |\n";
            cout << "|     " << board[i][0] << "      |     " << board[i][1] << "      |     " << board[i][2] << "      |\n";
            cout << "|____________|____________|____________|\n";
        }
    }

    bool checkWinner() const 
    {
        for (int i = 0; i < 3; ++i) 
        {
            if ((board[i][0] == currentMarker && board[i][1] == currentMarker && board[i][2] == currentMarker) ||
                (board[0][i] == currentMarker && board[1][i] == currentMarker && board[2][i] == currentMarker)) 
            {
                displayBoard();
                cout << "Player " << currentPlayer << " wins! Congratulations!\n";
                return true;
            }
        }

        if ((board[0][0] == currentMarker && board[1][1] == currentMarker && board[2][2] == currentMarker) ||
            (board[0][2] == currentMarker && board[1][1] == currentMarker && board[2][0] == currentMarker)) 
        {
            displayBoard();
            cout << "Player " << currentPlayer << " wins! Congratulations!\n";
            return true;
        }

        if (moves == 9) 
        {
            displayBoard();
            cout << "It's a tie!\n";
            return true;
        }
        return false;
    }

    void resetBoard() 
    {
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                board[i][j] = ' ';
            }
        }
        moves = 0;
    }

    void switchPlayer() 
    {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        currentMarker = (currentPlayer == 1) ? (player1 == "X" ? 'X' : 'O') : (player2 == "X" ? 'X' : 'O');
    }

public:
    TicTacToe() 
    {
        resetBoard();
    }

    void play() 
    {
        cout << "Tic Tac Toe\n";
        cout << "Player one, do you want to be X or O?\n";

        while (true) 
        {
            cin >> player1;
            if (player1 == "X") 
            {
                player2 = "O";
                break;
            } 
            else if (player1 == "O") 
            {
                player2 = "X";
                break;
            } 
            else 
            {
                cout << "Invalid choice, input X or O\n";
            }
        }

        currentPlayer = 1;
        currentMarker = (player1 == "X") ? 'X' : 'O';

        while (true) 
        {
            displayBoard();
            cout << "Player " << currentPlayer << "'s turn (" << currentMarker << "). Enter a slot (1-9): ";
            int slot;
            cin >> slot;

            if (cin.fail() || slot < 1 || slot > 9) 
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Choose a number between 1 and 9.\n";
                continue;
            }

            int row = (slot - 1) / 3;
            int col = (slot - 1) % 3;

            if (board[row][col] != ' ') 
            {
                cout << "Slot already taken! Try again.\n";
                continue;
            }

            board[row][col] = currentMarker;
            moves++;

            if (checkWinner()) 
            {
                askReplay();
                return;
            }

            switchPlayer();
        }
    }

    void askReplay() 
    {
        while (true) 
        {
            cout << "Do you want to play again? yes/no: ";
            string input;
            cin >> input;
            if (input == "yes") 
            {
                resetBoard();
                play();
                break;
            } 
            else if (input == "no") 
            {
                cout << "Thanks for playing!\n";
                break;
            } 
            else 
            {
                cout << "Invalid input, choose yes or no!\n";
            }
        }
    }
};

int main() 
{
    TicTacToe game;
    game.play();
    return 0;
}
