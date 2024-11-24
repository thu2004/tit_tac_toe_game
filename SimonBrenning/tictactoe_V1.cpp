#include <iostream>
#include <cstdlib>


void printBoard(char (&arr)[3][3]){
    // system("cls"); //clear terminal

    for (int i = 0; i < 3; i++){
        std::cout << " ";
        
        std::cout << arr[i][0] << " | ";
        std::cout << arr[i][1] << " | ";
        std::cout << arr[i][2] << " ";

        std::cout << "\n---|---|---\n";
    }
}

bool isEmpty(char (&arr)[3][3], int a, int b){
    if (arr[a][b] != 'x' && arr[a][b] != 'X' && arr[a][b] != 'o' && arr[a][b] != 'O'){
        return true;
    }
    return false;
}

bool checkWin(char (&arr)[3][3], char currentPlayer){

    //horizontal checks
    if (arr[0][0] == currentPlayer && arr[0][1] == currentPlayer && arr[0][2] == currentPlayer)
        return true;
    if (arr[1][0] == currentPlayer && arr[1][1] == currentPlayer && arr[1][2] == currentPlayer)
        return true;
    if (arr[2][0] == currentPlayer && arr[2][1] == currentPlayer && arr[2][2] == currentPlayer)
        return true;

    //vertical checks
    if (arr[0][0] == currentPlayer && arr[1][0] == currentPlayer && arr[2][0] == currentPlayer)
        return true;
    if (arr[0][1] == currentPlayer && arr[1][1] == currentPlayer && arr[2][1] == currentPlayer)
        return true;
    if (arr[0][2] == currentPlayer && arr[1][2] == currentPlayer && arr[2][2] == currentPlayer)
        return true;

    //diagonal checks
    if (arr[0][0] == currentPlayer && arr[1][1] == currentPlayer && arr[2][2] == currentPlayer)
        return true;
    if (arr[0][2] == currentPlayer && arr[1][1] == currentPlayer && arr[2][0] == currentPlayer)
        return true;

    return false;
}

bool checkDraw(char (&arr)[3][3]){
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            if (arr[i][j] != 'X' || arr[i][j] != 'O')
                return false;
    }
    return true;
}


int main(){
    char board[3][3]{
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    }; 

    bool gameRunning = true;
    char currentPlayer = 'X';
    
    while (gameRunning){
        system("cls");
        printBoard(board);

        int choice_x, choice_z;

        std::cout << "current player: " << currentPlayer << "\n";
        std::cout << "row (1-3) > "; 
        std::cin >> choice_x;
        std::cout << "column (1-3) > "; 
        std::cin >> choice_z;

        choice_x--; choice_z--;
        
        if (isEmpty(board, choice_x, choice_z)){
            board[choice_x][choice_z] = currentPlayer;
        }
        else{
            std::cout << "slot taken\n";
            system("pause");
            continue;
        }

        if (checkWin(board, currentPlayer)){
            printBoard(board);
            std::cout << "WINNER: " << currentPlayer << "\n";
            system("pause");
            exit(0);
        }

        if (checkDraw(board)){
            printBoard(board);
            std::cout << "GAME DRAW!\n";
            system("pause");
            exit(0);
        }

        if (currentPlayer == 'X')
            currentPlayer = 'O';
        else
            currentPlayer = 'X';
    }

    return 0;
}