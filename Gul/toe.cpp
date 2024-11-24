#include <iostream>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>

using namespace std;

class Board {
public:
    char* board;  // Dynamisk allokering för brädan (9 celler)

    // Konstruktor
    Board() {
        board = new char[9];  // Allokera minne för 9 celler
        for (int i = 0; i < 9; i++) {
            board[i] = ' ';  // Initiera brädan med tomma celler
        }
    }

    // Destruktor
    ~Board() {
        delete[] board;  // Frigör det dynamiskt allokerade minnet
    }

    // Funktion för att skriva ut brädan med färger och numrering från 1 till 9
    void printBoard(int cursorPos) {
        cout << "Tic-Tac-Toe Game\n\n";
        cout << "Player 1: X | Player 2: O\n\n";

        for (int i = 0; i < 9; ++i) {
            // Sätt färg beroende på om det är X eller O
            if (board[i] == 'X') {
                setColor(34);  // Blå för X
            } else if (board[i] == 'O') {
                setColor(31);  // Röd för O
            } else {
                setColor(37);  // Vit för tomma celler
            }

            // Om vi är på den aktuella markören, gör den synlig
            if (i == cursorPos) {
                setColor(33); // Gul för markören
            }

            // Skriv ut varje cell på brädan
            if (board[i] == ' ') {
                cout << " " << (i + 1) << " ";  // Skriv ut nummer om cellen är tom
            } else {
                cout << " " << board[i] << " ";  // Skriv ut X eller O om cellen är fylld
            }

            // Skriv ut vertikala linjer
            if (i % 3 != 2) {
                cout << "|";
            }

            // Skriv ut radbyte efter varje tredje cell
            if (i % 3 == 2 && i != 8) {
                cout << "\n---+---+---\n";
            }

            resetColor();  // Återställ färgen
        }
        cout << endl;
    }

    // Funktion för att hantera spelarens input via piltangenter
    bool handleInput(int& cursorPos, char currentPlayer) {
        while (true) {
            // Rensa terminalen och skriv ut brädan
            system("clear");
            printBoard(cursorPos);

            // Läs in tangenttryckning
            char ch = getKeyPress();

            // Hantera piltangenter (a, s, w, d)
            if (ch == 'w' || ch == 'W') { // Piltangent upp
                if (cursorPos >= 3) cursorPos -= 3;
            } else if (ch == 's' || ch == 'S') { // Piltangent ner
                if (cursorPos < 6) cursorPos += 3;
            } else if (ch == 'a' || ch == 'A') { // Piltangent vänster
                if (cursorPos % 3 != 0) cursorPos -= 1;
            } else if (ch == 'd' || ch == 'D') { // Piltangent höger
                if (cursorPos % 3 != 2) cursorPos += 1;
            } else if (ch == 'f' || ch == 'F') { // F-tangent för att göra draget
                // Kontrollera om cellen är tom
                if (board[cursorPos] == ' ') {
                    board[cursorPos] = currentPlayer;  // Placera X eller O
                    return true;  // Giltigt drag
                } else {
                    cout << "Cell is already occupied, try another one.\n";
                }
            }
        }
    }

    // Kontrollera om någon har vunnit
    char checkWinner() {
        // Kontrollera rader
        for (int i = 0; i < 3; ++i) {
            if (board[i * 3] != ' ' && board[i * 3] == board[i * 3 + 1] && board[i * 3] == board[i * 3 + 2]) {
                return board[i * 3];
            }
        }

        // Kontrollera kolumner
        for (int i = 0; i < 3; ++i) {
            if (board[i] != ' ' && board[i] == board[i + 3] && board[i] == board[i + 6]) {
                return board[i];
            }
        }

        // Kontrollera diagonaler
        if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) {
            return board[0];
        }
        if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) {
            return board[2];
        }

        return ' ';  // Ingen vinnare
    }

    // Kontrollera om brädan är full
    bool isFull() {
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                return false;  // Finns en tom cell, så brädan är inte full
            }
        }
        return true;  // Alla celler är fyllda
    }

private:
    // Funktion för att sätta färgen med ANSI escape-koder
    void setColor(int color) {
        cout << "\033[" << color << "m";
    }

    // Funktion för att återställa färgen till standard
    void resetColor() {
        cout << "\033[0m";
    }

    // Funktion för att läsa in en tangenttryckning utan att behöva trycka Enter
    char getKeyPress() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);  // Spara nuvarande terminalinställningar
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);  // Gör så att vi kan läsa in en tangent direkt
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Återställ terminalinställningarna
        return ch;
    }
};

class Game {
public:
    Board board;   // Skapar ett bräde
    char currentPlayer;  // Aktuell spelare ('X' eller 'O')
    int cursorPos;  // Markörens position på brädan

    Game() {
        currentPlayer = 'X';  // Starta med spelare X
        cursorPos = 0;  // Starta på cell 1 (index 0)
    }

    void start() {
        while (true) {
            // Hantera spelarens input
            if (board.handleInput(cursorPos, currentPlayer)) {
                // Kontrollera om någon har vunnit
                char winner = board.checkWinner();
                if (winner != ' ') {
                    system("clear");
                    board.printBoard(cursorPos);
                    cout << "Player " << winner << " wins!" << endl;
                    break;
                }
                
                // Kontrollera om brädan är full
                if (board.isFull()) {
                    system("clear");
                    board.printBoard(cursorPos);
                    cout << "The game is a draw!" << endl;
                    break;
                }

                // Byt spelare
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
    }
};

int main() {
    Game game;  // Skapa ett spel
    game.start();  // Starta spelet
    return 0;
}
