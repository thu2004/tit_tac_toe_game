#include <iostream>
#include <string>

using namespace std;

void gameBoard(const char board[3][3]);
void gameLoop();
void playAgain();
bool checkWinner(char board[3][3], char cMarker, int cPlayer, int moves);

int main()
{
    gameLoop();
    return 0;
}

void gameBoard(const char board[3][3]) 
{
    
    cout << " ______________________________________\n";
    for (int i = 0; i < 3; ++i) 
    {
        cout << "|            |            |            |\n";
        cout << "|     " << board[i][0] << "      |     " << board[i][1] << "      |     " << board[i][2] << "      |\n";
        cout << "|____________|____________|____________|\n";
    }
    
}  
void gameLoop()
{
    string player1;
    string player2;
    string X = "X";
    string O = "O";
    int cPlayer;
    char cMarker;
    int moves;

    char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    cout << "Tic Tac Toe" << endl;
    cout << "Player one, do you want to be X or O?" << endl;
    
    do
    {
        
        cin >> player1;
        if(player1 == X)
        {
            cout << "You choose X" << endl;
            cout << "Player two are O" << endl;
            player2 = "O";
            break;
        }
        else if(player1 == O)
        {
            cout << "You choose O" << endl;
            cout << "Player two are X" << endl;
            player2 = "X";
            break;
        }
        else
        {
            cout << "Invalid choice, input X or O" << endl;

        }
    }while(true);

    cPlayer = 1;
    cMarker = (player1 == "X") ? 'X' : 'O';
    moves = 0;
        
    while(true)
    {
        gameBoard(board);
        cout << "Player " << cPlayer << "'s turn (" << cMarker << "). Enter a slot (1-9): ";
        int slot;
        cin >> slot;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Choose a number between 1 and 9" << endl;
            continue;
        }

        if (slot < 1 || slot > 9) 
        {
            cout << "Invalid slot! Choose a number between 1 and 9.\n";
            continue;
        }

        int row = (slot - 1) / 3; 
        int col = (slot - 1) % 3; 

        if (board[row][col] != ' ') 
        {
            cout << "Slot already taken! Try again.\n";
            continue;
        }

        board[row][col] = cMarker;
        moves++;

        if(checkWinner(board, cMarker, cPlayer, moves))
        {
            playAgain();
            return;
        }
    
    
        cPlayer = (cPlayer == 1) ? 2 : 1;
        cMarker = (cPlayer == 1) ? (player1 == "X" ? 'X' : 'O') : (player2 == "X" ? 'X' : 'O');    
    }
    
}

void playAgain()
{
    do
    {
        cout << "Do you want to play again? yes/no ";
        string input;
        cin >> input;
        if(input == "yes")
        {
            gameLoop();
            break;
        }
        else if(input == "no")
        {
            cout << "Thank for playing!" << endl;
            break;
        }
        else
        {
            cout << "Invalid input, choose yes or no!" << endl;
        }  
    }while(true);
}

bool checkWinner(char board[3][3], char cMarker, int cPlayer, int moves) 
{
    for (int i = 0; i < 3; ++i) 
    {
        if ((board[i][0] == cMarker && board[i][1] == cMarker && board[i][2] == cMarker) ||
            (board[0][i] == cMarker && board[1][i] == cMarker && board[2][i] == cMarker)) 
        {
            gameBoard(board);
            cout << "Player " << cPlayer << " wins! Congratulations!\n"; 
            return true;
        }
    }
        
    if ((board[0][0] == cMarker && board[1][1] == cMarker && board[2][2] == cMarker) ||
        (board[0][2] == cMarker && board[1][1] == cMarker && board[2][0] == cMarker)) 
    {
        gameBoard(board);
        cout << "Player " << cPlayer << " wins! Congratulations!\n"; 
        return true;
    }

    if (moves == 9) 
    {
        gameBoard(board);
        cout << "It's a tie!\n";
        return true;
    }
    return false;
}
