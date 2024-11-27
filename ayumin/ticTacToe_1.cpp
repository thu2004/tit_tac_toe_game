#include <iostream>

char board[3][3] = {{'1', '2', '3'}, {'4', '5','6'}, {'7', '8', '9'}};
char player = 'X';
int row,column;

bool running = true;

void drawBoard();
void playerMove();
bool checkWinner();
bool checkTie();


int main()
{
    while(running){

        // intro
        std::cout << "Tic Tac Toe Game \n";
        std::cout << "Player1[X] Player2[O] Quit(99)\n";
        
        drawBoard();
        playerMove();

        if(checkWinner()){
            std::cout << "Player: " << player << " wins!" << std::endl;
            running = false;
            break;
        }
        else if(checkTie()){
            std::cout << "It's a tie!" << std::endl;
            running = false;
            break;
         }
        player = (player == 'X') ? 'O' : 'X';

    }
    // ending
    std::cout << "Thanks for playing! \n";
    std::cout << "^._.^ ♡♡ \n \n";



    return 0;
}

void drawBoard(){

    std::cout << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << '\n';
}


void playerMove(){
    int choice;

    if (player == 'X')
    std::cout << "Player1 [x] turn: \n";

    if (player == 'O')
    std::cout << "player2 [O] turn: \n";

    std::cin >> choice;
    switch(choice){
        case 99: running = false; std::cout <<"You quited!\n";break;
        case 1: row = 0; column = 0; break;
        case 2: row = 0; column = 1; break;
        case 3: row = 0; column = 2; break;
        case 4: row = 1; column = 0; break;
        case 5: row = 1; column = 1; break;
        case 6: row = 1; column = 2; break;
        case 7: row = 2; column = 0; break;
        case 8: row = 2; column = 1; break;
        case 9: row = 2; column = 2; break;

        default:
            std::cout << "Invalid Operation\n";
            break;

    }


    if (player == 'X' && board[row][column]!= 'X' && board[row][column] != 'O'){
        board[row][column] = 'X';
        // Example a variable for player: player = (player == 'X') ? 'O' : 'X';
    }

    else if (player == 'O' && board[row][column]!= 'X' && board[row][column] != 'O'){
        board[row][column] = 'O';

    }

    else{
        std::cout << "Box already filled! \n Please try again!";
        playerMove();
    }
}


bool checkWinner()
{
    for (int i = 0; i < 3; ++i) // loop 1-3
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // Row check
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) // column
        {
            return true;
        }
    }
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // Diagonal check
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        {
        return true;
        }
    return false;
}

  
bool checkTie() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // empty space left on the board
            }
        }
    }
    return true;
}

