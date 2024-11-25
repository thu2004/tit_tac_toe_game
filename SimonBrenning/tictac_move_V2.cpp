#include <iostream>
#include <conio.h>

// class gameBoard{
// public:



// };


char game_board[3][3] = {                    
{' ',' ',' '}, 
{' ',' ',' '},
{' ',' ',' '}
};

int posHorizontal = 1;  //startpos i gameboard = ruta 5/mitten
int posVertical = 1;

void clearScreen() {
    std::printf("\033[H\033[J"); 
}


void print_game_board(char board[3][3], bool player) {

    char cPlayer = player ? 'X' : 'O';
    
    std::cout << "current player: " << cPlayer << "\n";
    std::cout << "|---|---|---|\n";
    for (int i = 0; i < 3; i++){    //horizontal
        std::cout << '|';

        for (int j = 0; j < 3; j++){    //vertical
            if (i == posVertical && j == posHorizontal){
                std::cout << '[' << board[i][j] << ']' << '|';
            }
            else{
                std::cout << ' ' << board[i][j] << ' ' << '|';
            }

        }

        std::cout << "\n|---|---|---|\n";
    }


}


bool checkWin(char board[3][3], bool player){
    char currentPlayer = player ? 'X' : 'O';

            //horizontal win checks 
    if ((board[0][0] == currentPlayer && board[0][1] == currentPlayer && board[0][2] == currentPlayer) ||
        (board[1][0] == currentPlayer && board[1][1] == currentPlayer && board[1][2] == currentPlayer) ||
        (board[2][0] == currentPlayer && board[2][1] == currentPlayer && board[2][2] == currentPlayer)){
            return true;
        }

        //vertical win checks
     if ((board[0][0] == currentPlayer && board[1][0] == currentPlayer && board[2][0] == currentPlayer) ||
        (board[0][1] == currentPlayer && board[1][1] == currentPlayer && board[2][1] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][2] == currentPlayer && board[2][2] == currentPlayer)){
            return true;
        }

        //diagonal win checks
     if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)){
            return true;
        }
    else
        return false;
}




bool place_on_board(char board[3][3], int vertical_pos, int horizontal_pos, bool player)
{
    //!player == player2, player = player1
    //true =  X
    //false = O

    
    if(player)
    {
        board[vertical_pos][horizontal_pos] = 'X';
    }
    else
    {
        board[vertical_pos][horizontal_pos] = 'O';
    }

    if (checkWin(board, player))
    {
        clearScreen();
        print_game_board(game_board, player);
        std::cout << (player ? "Player X wins!\n" : "Player O wins!\n");
        system("pause");
        exit(0);
    }

    return true;
}





void moveCursor(char board[3][3], bool player){      //move cursor. returns true if move successful

    char key; 

    while(true)
    {

        clearScreen();
        print_game_board(game_board, player);

        key = _getch();

        if (key == -32 || key == 224) { // Kontrollera escape-sekvens
            key = _getch(); // Läs andra tecknet

        switch (key)
        {
        case 72: //up
            if(posVertical == 0)
                posVertical = 2;
            else
                posVertical--;
            break;

        case 80: //down
            if(posVertical == 2)
                posVertical = 0;
            else
                posVertical++;
            break;

        case 75: //left
            if(posHorizontal == 0)
                posHorizontal = 2;
            else
                posHorizontal-= 1;
            break;

        case 77: //right
            if(posHorizontal == 2)
                posHorizontal = 0;
            else
                posHorizontal += 1;
            break;

        default:
            std::cout << "Invalid command!\n";
            break;
        }


        //look for enter input 

        }
        else if(key == '\r')
        {
            if(board[posVertical][posHorizontal] != 'X' && board[posVertical][posHorizontal] != 'O'){
                
                place_on_board(game_board, posVertical, posHorizontal, player);
                
                if (player)
                {
                    player = false;
                }else
                    player = true;

                
            }

            else{
                std::cout << "That spot is already taken!\n";
                _getch();
            }
        } 
    }
}




int main(int argc, char const *argv[])
{
    
    bool player = true;
    
    moveCursor(game_board, player);


    

    return 0;
}



// index 1 5 9 == x or o
// index (0,2), (4,6), (8,10) == []

//    |   |   
// ---|---|---
//    |   |  
// ---|---|---
//    |   |



//gameboard
// {' ', ' ', ' '} //ruta 1
// {' ', ' ', ' '} //ruta 2
// {' ', ' ', ' '} //ruta 3
// {' ', ' ', ' '} //ruta 4
// {' ', ' ', ' '} //ruta 5
// {' ', ' ', ' '} //ruta 6
// {' ', ' ', ' '} //ruta 7
// {' ', ' ', ' '} //ruta 8
// {' ', ' ', ' '} //ruta 9