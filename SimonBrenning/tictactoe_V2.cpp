#include <iostream>


class Game{
private:
    char gameBoard[3][3]{
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };


public:
void printBoard(){
    system("cls");
    
    for (int i = 0; i < 3; i++){                //prints game board
        std::cout << " ";
        std::cout << gameBoard[i][0] << " | ";
        std::cout << gameBoard[i][1] << " | ";
        std::cout << gameBoard[i][2] << " ";

        std::cout << "\n---|---|---\n";
    }
    std::cout << "\n";
}


bool playRound(const int& input, const char& currentPlayer){    //returns true if successful operation
    for (int i = 0; i < 3; i++){                                //returns false if unsuccessful
        for (int j = 0; j < 3; j++){
            if (gameBoard[i][j] == '0' + input){    //checks if input number is free on the board
                gameBoard[i][j] = currentPlayer;    //sets board spot to player mark
                return true;
            }
        }
    }
    std::cout << "spot taken\n";    //if input number is not found
    return false;
}


bool checkWin(char player){
        //horizontal win checks 
    if ((gameBoard[0][0] == player && gameBoard[0][1] == player && gameBoard[0][2] == player) ||
        (gameBoard[1][0] == player && gameBoard[1][1] == player && gameBoard[1][2] == player) ||
        (gameBoard[2][0] == player && gameBoard[2][1] == player && gameBoard[2][2] == player)){
            return true;
        }

        //vertical win checks
    if ((gameBoard[0][0] == player && gameBoard[1][0] == player && gameBoard[2][0] == player) ||
        (gameBoard[0][1] == player && gameBoard[1][1] == player && gameBoard[2][1] == player) ||
        (gameBoard[0][2] == player && gameBoard[1][2] == player && gameBoard[2][2] == player)){
            return true;
        }

        //diagonal win checks
    if ((gameBoard[0][0] == player && gameBoard[1][1] == player && gameBoard[2][2] == player) ||
        (gameBoard[0][2] == player && gameBoard[1][1] == player && gameBoard[2][0] == player)){
            return true;
        }

    return false;
}


bool checkDraw(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (gameBoard[i][j] != 'X' && gameBoard[i][j] != 'O'){  //if not taken by player
                return false;
            }
        }
    }
    return true;
}

};



int main(){
    Game game;

    char currentPlayer = 'X'; 

    while (true){

        game.printBoard();

        int userInput;
        std::cout << "current player: " << currentPlayer << "\n";
        std::cout << "enter slot: > "; std::cin >> userInput;

        if (!game.playRound(userInput, currentPlayer)){
            system("pause");
            continue;
        }

        if (game.checkWin(currentPlayer)){
            game.printBoard();
            std::cout << "Player " << currentPlayer << " WON!\n";
            system("pause");
            exit(0);
        }

        if (game.checkDraw()){
            game.printBoard();
            std::cout << "GAME DRAW!\n";
            system("pause");
            exit(0);
        }

        if (currentPlayer == 'X')   //sets next round to other player
            currentPlayer = 'O';
        else currentPlayer = 'X';
    }






    return 0;
}