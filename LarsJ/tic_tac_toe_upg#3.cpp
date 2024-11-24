#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <limits> // för input gränser

using namespace std;

class Terminal {
public:
    Terminal(){
        tcgetattr(STDIN_FILENO, &old_term);
        struct termios new_term = old_term;
        new_term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    }

    ~Terminal() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    }

    char getch() {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        return ch;
    }

private:
    struct termios old_term;
};

class Board {
    char board[3][3]; // Attribut: 3x3-bräde

public:
    Board() { // konstruktor
        int num = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '0' + num++; //Fyll med 1-9
            }
        }
    }

    void display(int cursorRow, int cursorCol) const { //Visa brädet
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == cursorRow && j == cursorCol) {
                    cout << "[" << board[i][j] << "]";
                } else {
                    cout << " " << board[i][j] << " ";
                }
                if (j < 2) cout << "|"; // skriv ut "|" mellan kolumner
            }
            cout << endl; // ny rad efter varje rad
            if (i < 2) cout << "---+---+---" << endl; //separator mellan rader
        }
    }

    bool updateBoard(int row, int col, char symbol) {  //Uppdatera brädet
        //kolla om platsen är ledig
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = symbol; //placera spelarens symbol
            return true; // uppdaterad
        }
        return false; // platsen är inte ledig
    }

    bool checkWin() const { // Kontrollera om en spelare har vunnit
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
        return false; 
    }

    bool checkDraw() const { // Kontrollera om spelet är oavgjort
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
    int cursorRow, cursorCol; // "pekare" variabler

    Terminal terminal;

    void clearConsole() { // rensa konsolen med nya rader
        //for (int i = 0; i < 50; i++) {
        //    cout << "\n";
        cout << "\033[2J\033[1;1H"; // rensa skärmen (ANSI esc-sekvens)
    }

public:
    Game() : gameRunning(true), currentPlayer(0), cursorRow(0), cursorCol(0) {}

    void playTurn() { // Hantera en spelares tur/runda
        char playerSymbol = (currentPlayer == 0) ? 'X' : 'O';

        while (true) {
            clearConsole();
            board.display(cursorRow, cursorCol);
            
            cout << "Player " << playerSymbol << ", use arrow keys to move. Press Enter to select.\n";
            char key = terminal.getch();

            if (key == '\033'){
                char next = terminal.getch();
                if (next == '[') {
                    char arrow = terminal.getch();
                    switch (arrow) {
                        case 'A': // Up
                            if (cursorRow > 0) cursorRow--;
                            break;
                        case 'B': // Down
                            if (cursorRow < 2) cursorRow++;
                            break;
                        case 'C': // Right
                            if (cursorCol < 2) cursorCol++;
                            break;
                        case 'D': // Left
                            if (cursorCol > 0) cursorCol--;
                            break;                        
                    }
                }
            } else if (key == '\n') { //Enter
                if (board.updateBoard(cursorRow, cursorCol, playerSymbol)) break;
                cout << "Cell is already taken. Try another.\n";
            }
        }
    }

    void start() { //starta spel-loopen
        cout << "Welcome to Tic-Tac-Toe!\n";

        while (gameRunning) {
            playTurn(); // spela en runda
            if (board.checkWin()) {
                clearConsole();
                board.display(cursorRow, cursorCol);
                cout << "Player " << ((currentPlayer == 0) ? 'X' : 'O') << " wins!\n";
                gameRunning = false;
            } else if (board.checkDraw()) {
                clearConsole();
                board.display(cursorRow, cursorCol);
                cout << "It's a draw!\n";
                gameRunning = false;
            }
            currentPlayer = 1 - currentPlayer; // växla spelare
        }
    }
};

int main() {

    Game game; // skapa ett spelobjekt
    game.start(); // starta spelet

    return 0;
}
