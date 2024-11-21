#include <iostream>
#include <limits> // för input gränser

using namespace std;

class Board {
    char board[3][3]; // Attribut: 3x3-bräde

public:
    Board() { // konstruktor
        int num = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '0' + num; //Fyll med 1-9
                num++;
            }
        }
    }

    void display() { //Visa brädet
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << " " << board[i][j];
                if (j < 2) cout << " |"; // skriv ut "|" mellan kolumner
            }
            cout << endl; // ny rad efter varje rad
            if (i < 2 ) cout << "---+---+---" << endl; //separator mellan rader
        }
    }

    bool updateBoard(int choice, char symbol) {  //Uppdatera brädet
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;
        //kolla om platsen är ledig
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = symbol; //placera spelarens symbol
            return true; // uppdaterad
        }
        return false; // platsen är inte ledig
    }

    bool checkWin() { // Kontrollera om en spelare har vunnit
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        }
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
        return false; 
    }

    bool checkDraw() { // Kontrollera om spelet är oavgjort
        for (int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') return false;
            }
        }
        return true; // ingen vinst
    }
};

class Game {
    Board board; // instans av Board-klassen
    bool gameRunning; // Status för om spelet pågår
    int currentPlayer; // Spelaren som har turen (0 = X, 1 = 'O')

    void clearConsole() { // rensa konsolen med nya rader
        for (int i = 0; i < 50; i++) {
            cout << "\n";
        }
    }

public:
    Game() : gameRunning(true), currentPlayer(0) {}

    void playTurn() { // Hantera en spelares tur/runda
        char playerSymbol = (currentPlayer == 0) ? 'X' : 'O';
        int choice;

        while (true) {
            cout << "Player " << playerSymbol << ", choose a position (1-9): ";
            cin >> choice;

            //validera input
            if (cin.fail() || choice < 1 || choice > 9) {
                cin.clear(); //rensa felstatus för cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignorera fel input
                cout << "Invalid input. Please enter a number between 1 and 9.\n";
                continue;
            }

            // försök upd brädet
            if (board.updateBoard(choice, playerSymbol)) {
                break; // validerad och uppdaterad, gå vidare
            } else {
                cout << "Position already taken. Try again.\n";
            }
        }
    }

    void start() { //starta spel-loopen
        cout << "\nWelcome to Tic-Tac-Toe!\n";
        cout << "Players take turn placing their marks (X or O) on the board.\n\n";

        bool firstRun = true; // flagga för undvika rensning

        while (gameRunning) {
            if (!firstRun) {
                clearConsole(); // rensa konsolen om det inte är första iterationen
            }
            firstRun = false; // nollställ flaggan
            board.display(); // Visa brädet

            playTurn(); // spela en runda

            if (board.checkWin()) {
                clearConsole();
                board.display();
                cout << "\nPlayer " << ((currentPlayer == 0) ? 'X' : 'O') << " wins!\n";
                gameRunning = false;
            } else if (board.checkDraw()) {
                clearConsole();
                board.display();
                cout << "\nIt's a draw!\n";
                gameRunning = false;
            }
            // växla spelare
            currentPlayer = 1 - currentPlayer;
        }
    }
};

int main() {

    Game game; // skapa ett spelobjekt
    game.start(); // starta spelet

    return 0;
}