#include <iostream>
#include <unistd.h>
#include <termios.h>

using namespace std;

class TicTacToe 
{
private:
    char board[3][3];
    string player1, player2;
    char currentMarker;
    int currentPlayer;
    int moves;

    void clearScreen() const 
    {
        // ANSI escape code to clear the screen and move the cursor to the top-left corner
        cout << "\033[2J\033[H";
    }

   void displayBoard(int selectedRow, int selectedCol) const 
    {
        clearScreen(); 
        cout << " _____________________________\n";
        for (int i = 0; i < 3; ++i) 
        {
            cout << "|         |         |         |\n";
            for (int j = 0; j < 3; ++j) 
            {
                cout << "|";
                if (i == selectedRow && j == selectedCol)
                    cout << "   [" << board[i][j] << "]   "; 
                else
                    cout << "    " << board[i][j] << "    ";
            }
            cout << "|\n";
            cout << "|_________|_________|_________|\n";
        }
    }


    bool checkWinner() const 
    {
        for (int i = 0; i < 3; ++i) 
        {
            if ((board[i][0] == currentMarker && board[i][1] == currentMarker && board[i][2] == currentMarker) ||
                (board[0][i] == currentMarker && board[1][i] == currentMarker && board[2][i] == currentMarker)) 
            {
                displayBoard(-1, -1);
                cout << "Player " << currentPlayer << " wins! Congratulations!\n";
                return true;
            }
        }

        if ((board[0][0] == currentMarker && board[1][1] == currentMarker && board[2][2] == currentMarker) ||
            (board[0][2] == currentMarker && board[1][1] == currentMarker && board[2][0] == currentMarker)) 
        {
            displayBoard(-1, -1);
            cout << "Player " << currentPlayer << " wins! Congratulations!\n";
            return true;
        }

        if (moves == 9) 
        {
            displayBoard(-1, -1);
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

    char getKeyInput() const 
    {
        struct termios oldt, newt;
        char ch;

        // Get the terminal settings for stdin
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;

        // Disable canonical mode and echo
        newt.c_lflag &= ~(ICANON | ECHO);

        // Set the new attributes
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        // Read the character
        read(STDIN_FILENO, &ch, 1);

        // Restore the original settings
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
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

        int selectedRow = 0, selectedCol = 0;

        while (true) 
        {
            displayBoard(selectedRow, selectedCol);
            cout << "Player " << currentPlayer << "'s turn (" << currentMarker << "). Use arrow keys to move, and press Enter to select.\n";

            char input = getKeyInput();

            if (input == '\033') 
            {
                getKeyInput(); // Skip the '['
                switch (getKeyInput())
                {
                    case 'A': // Up
                        selectedRow = (selectedRow - 1 + 3) % 3;
                        break;
                    case 'B': // Down
                        selectedRow = (selectedRow + 1) % 3;
                        break;
                    case 'C': // Right
                        selectedCol = (selectedCol + 1) % 3;
                        break;
                    case 'D': // Left
                        selectedCol = (selectedCol - 1 + 3) % 3;
                        break;
                }
            }
            else if (input == '\n') 
            {
                if (board[selectedRow][selectedCol] == ' ')
                {
                    board[selectedRow][selectedCol] = currentMarker;
                    moves++;

                    if (checkWinner()) 
                    {
                        askReplay();
                        return;
                    }

                    switchPlayer();
                }
                else
                {
                    cout << "Slot already taken! Try again.\n";
                    usleep(1000000); // Pause for 1 second
                }
            }
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
