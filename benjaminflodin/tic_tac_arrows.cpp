#include <iostream>
#include <conio.h>

// class gameBoard{
// public:



// };


char game_board[3][9] = {                           // index (0,2), (4,6), (8,10) == [] // index 1 4 7 == spot for player marker
{' ',' ',' ',' ',' ',' ',' ',' ',' '}, 
{' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' '}
};


void clearScreen() {
    std::printf("\033[H\033[J"); 
}


//prova igen :)

void print_game_board(char board[3][9])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            std::cout << board[i][j];
            if(j == 2 || j == 5)
            {
                std::cout << '|';
            }
        }
        std::cout << std::endl;
        if (i < 2)
            std::cout << "---|---|---\n";
    }
}



bool checkWin(char board[3][9], bool player){
    char currentPlayer = player ? 'X' : 'O';

            //horizontal win checks 
    if ((board[0][1] == currentPlayer && board[0][4] == currentPlayer && board[0][7] == currentPlayer) ||
        (board[1][1] == currentPlayer && board[1][4] == currentPlayer && board[1][7] == currentPlayer) ||
        (board[2][1] == currentPlayer && board[2][4] == currentPlayer && board[2][7] == currentPlayer)){
            return true;
        }

        //vertical win checks
     if ((board[0][1] == currentPlayer && board[1][1] == currentPlayer && board[2][1] == currentPlayer) ||
        (board[0][4] == currentPlayer && board[1][4] == currentPlayer && board[2][4] == currentPlayer) ||
        (board[0][7] == currentPlayer && board[1][7] == currentPlayer && board[2][7] == currentPlayer)){
            return true;
        }

        //diagonal win checks
     if ((board[0][1] == currentPlayer && board[1][4] == currentPlayer && board[2][7] == currentPlayer) ||
        (board[0][7] == currentPlayer && board[1][4] == currentPlayer && board[2][1] == currentPlayer)){
            return true;
        }
    else
        return false;
}




bool place_on_board(char board[3][9], int vertical_pos, int horizontal_pos, bool player)
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
        print_game_board(game_board);
        std::cout << "IASDUASDASODASJAS";
        std::cout << (player ? "Player X wins!\n" : "Player O wins!\n");
        system("pause");
    }

    return true;
}


void moveCursor(char board[3][9], bool player){      //move cursor. returns true if move successful

    int posHorizontal = 4;  //startpos = ruta 5
    int posVertical = 1;
    
    char key; 

    
    

    while(true)
    {

        
        board[posVertical][posHorizontal-1] = '[';
        board[posVertical][posHorizontal+1] = ']';  
        clearScreen();
        print_game_board(game_board);


        key = _getch();

        board[posVertical][posHorizontal-1] = ' '; //reset current pos before next loop
        board[posVertical][posHorizontal+1] = ' ';  

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
            if(posHorizontal == 1)
                posHorizontal = 7;
            else
                posHorizontal-= 3;
            break;

        case 77: //right
            if(posHorizontal == 7)
                posHorizontal = 1;
            else
                posHorizontal += 3;
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
    //print_game_board(game_board);
    //print_game_board(game_board);
    
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