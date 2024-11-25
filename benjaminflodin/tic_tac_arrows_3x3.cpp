#include <iostream>
#include <conio.h>

void clear_screen()
{
    std::printf("\033[H\033[J"); 
}

class Board{

    public:

        Board() {}

        char game_board [3][3] = { 
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'}
    };

};

class Game : public Board{

    public:

        Game() {}


        static void print_game_board(char board[3][3], int &row, int &column)
        {
            
            
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    if (i == row && j == column)
                        std::cout << "[" << board[i][j] << "]";
                    else
                        std::cout << " " << board[i][j] << " ";

                    if(j != 2)
                    {
                        std::cout << "|";
                    }
                }
                std::cout << std::endl;
                std::cout << "---|---|---";
                std::cout << std::endl;

            }
        }

        static bool checkWin(char board[3][3], bool &player){
            
            char currentPlayer = player ? 'X' : 'O';
            
            if ((board[0][0] == currentPlayer && board[0][1] == currentPlayer && board[0][2] == currentPlayer) ||
                (board[1][0] == currentPlayer && board[1][1] == currentPlayer && board[1][2] == currentPlayer) ||
                (board[2][0] == currentPlayer && board[2][1] == currentPlayer && board[2][2] == currentPlayer)){
                return true;
            }

            
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

        static void place_on_board(char board[3][3], int &row, int &column, bool &player)
        {
            //!player == player2, player = player1
            //true =  X
            //false = O

            if(player)
            {
                board[row][column] = 'X';
            }
            else
            {
                board[row][column] = 'O';
            }

            //checkWin(board, player);       
        }


        static bool movement(char board[3][3], int &row, int &column, bool &player1)
    {
        char key;
        key = _getch();

        if (key == -32 || key == 224) { // Kontrollera escape-sekvens
                key = _getch(); // Läs andra tecknet

            switch (key)
            {
            case 72: //up
                if(row != 0)
                    row--;
                break;

            case 80: //down
                if(row != 2)
                    row++;
                break;

            case 75: //left
                if(column != 0)
                    column--;
                break;

            case 77: //right
                if(column != 2)
                    column++;
                break;

            default:
                //std::cout << "Invalid command!\n";
                break;
            }

        }
        else if(key == '\r')
        {
            if(board[row][column] != 'X' && board[row][column] != 'O'){
                
                place_on_board(board, row, column, player1);
                
                if(checkWin(board, player1))
                    return true;               

                if (player1)
                {
                    player1 = false;
                }else
                    player1 = true;

                
            }

            else{
                std::cout << "That spot is already taken!\n";
                _getch();
            }
        } 
            return false;

    }

        


};



int main(int argc, char const *argv[])
{
    int row = 0;
    int col = 0;
    bool player1 = true;
    Board board;
    Game game;

    while(1)
    {
        
        clear_screen();
        game.print_game_board(board.game_board, row, col);             
        if(game.movement(board.game_board, row, col, player1))
            break;
        else
            continue;
    }

    std::cout << (player1? "Player x wins" : "Player O wins!");

    return 0;
}
