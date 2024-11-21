#include <iostream>
#include <limits> // för input gränser

using namespace std;

char board[3][3]; //brädan 2d array

// Function declarations
// rensa konsolen
void clearConsole() {
    for (int i = 0; i < 50; i++) {
        cout << "\n";
        }
    }

void displayBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) { //loopar igenom varje rad
        for (int j = 0; j < 3; j++) { //loopar igenom varje kolumn
            cout << " " << board[i][j]; // skriv ut symbolen eller mellanslaget
            if (j < 2) cout << " |"; // skriv ut "|" mellan kolumner
        }
        cout << endl; // ny rad efter varje rad
        if (i < 2) cout << "---+---+---" << endl; // separations linje
    }
}

// Funktion för att kolla om en spelare har vunnit
bool checkWin(char board[3][3]) { // visualizera med 0.0 0.1 0.2, 1.0 1.1 1.2, 2.0 2.1 2.2
    // kolla rader
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return true;
        }
    }

    // kolla kolumner
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return true;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return true;
    }

    return false; //ingen vinst
}

// Funktion att se om spelet är oavgjort
bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O'){
                return false; // det finns fortfarande tomma platser
            }
        }
    }
    return true; // brädet är fullt
}

int main() {
    char board[3][3] = {{'1', '2', '3'},
                        {'4', '5', '6'},
                        {'7', '8', '9'}}; // initiera brä'det med siffror

    bool gameRunning = true;
    int currentPlayer = 0; // 0 för spelare X, 1 för spelare O
    bool firstRun = true; // flagg för att undvika rens första gången

    cout << "==========================\n";
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Players take turns placing their marks (X or O) on the board.\n";
    cout << "To play, choose a number between 1-9 corresponding to the boar position.\n";
    cout << "Let's start!\n\n";


    while (gameRunning) { //huvud spel loop

        if (!firstRun) {
            clearConsole(); //rensa från och med andra körningen
        }
        firstRun = false;

        displayBoard(board); // visa brädet

        //spelarnas tur
        char playerSymbol = currentPlayer == 0 ? 'X' : 'O';
        cout << "\n";
        cout << "Player " << playerSymbol << "'s turn. Choose position (1-9): ";

        int choice;
        cin >> choice;

        //kolla att input är giltig med limits
        if (cin.fail() || choice < 1 || choice > 9) {
            cin.clear(); //rensa felstatus för cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignorera ogiltig input
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue; // be om input igen
        }

        //kolla att positionen är ledig och upd brädet
        bool validMove = false;
        for (int i = 0; i < 3 && !validMove; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '1' + (choice - 1)) { // kolla om cellen är ledig
                    board[i][j] = playerSymbol; // upd brädet med spelarens symbol
                    validMove = true;
                }
            }
        }

        if (!validMove) {
            cout << "Position already taken. Choose another position.\n";
            continue; // hoppa över resten av loopen och låt spelaren försöka igen
        }

        //koll vist eller oavgjort
        if (checkWin(board)){
            clearConsole();
            displayBoard(board);
            cout << "\n";
            cout << "Player " << playerSymbol << " wins!\n";
            gameRunning = false; 
        } else if (checkDraw(board)) {
            clearConsole();
            displayBoard(board);
            cout << "\n";
            cout << "It's a draw!\n";
            gameRunning = false;
        }
        //växla spelare
        currentPlayer = 1 - currentPlayer;
    }

    return 0;
}