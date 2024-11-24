#include <iostream>
#include <cstdlib> // För att använda system("clear") på UNIX-baserade system

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
    void printBoard() {
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

            // Skriv ut varje cell på brädan, numrera från 1 till 9
            if (board[i] == ' ') {
                cout << " " << (i + 1) << " "; // Skriv numret om det är tomt
            } else {
                cout << " " << board[i] << " "; // Skriv ut X eller O
            }

            // Skriv ut vertikala linjer
            if (i % 3 != 2) {
                cout << "|";
            }

            // Skriv ut radbyte efter varje tredje cell
            if (i % 3 == 2 && i != 8) {
                cout << "\n---+---+---\n";
            }
        }
        cout << endl;
    }

    // Kontrollera om brädan är full
    bool isFull() {
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                return false;  // Det finns minst en tom plats
            }
        }
        return true;  // Brädan är full
    }

    // Kontrollera om någon har vunnit
    char checkWinner() {
        int winningCombinations[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Horisontella
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Vertikala
            {0, 4, 8}, {2, 4, 6}               // Diagonala
        };

        for (int i = 0; i < 8; i++) {
            int index1 = winningCombinations[i][0];
            int index2 = winningCombinations[i][1];
            int index3 = winningCombinations[i][2];

            if (board[index1] == board[index2] && board[index2] == board[index3] && board[index1] != ' ') {
                return board[index1];  // Retur av vinnaren (X eller O)
            }
        }

        return ' ';  // Ingen vinnare
    }

    // Funktion för att hantera spelarens input
    bool handleInput(char currentPlayer) {
        int position;
        while (true) {
            cout << "Player " << (currentPlayer == 'X' ? "1" : "2") << ", choose a position (1-9): ";
            cin >> position;

            // Justera för 1-baserad indexering (positioner 1-9)
            position--;

            // Kontrollera att positionen är giltig och inte redan tagen
            if (position >= 0 && position < 9 && board[position] == ' ') {
                board[position] = currentPlayer;
                return true;  // Giltigt drag
            } else {
                cout << "Invalid or already taken position, try again.\n";
            }
        }
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
};

class Game {
public:
    Game() : currentPlayer('X'), gameOver(false) {
        board = new Board();  // Skapa ett objekt för brädan
    }

    ~Game() {
        delete board;  // Frigör minnet som används för brädan
    }

    // Starta spelet
    void start() {
        while (!gameOver) {
            system("clear");  // Rensa skärmen innan vi skriver ut brädan på nytt
            board->printBoard();  // Visa den aktuella brädan
            if (board->handleInput(currentPlayer)) {  // Hantera spelarens input
                // Kontrollera om det finns en vinnare
                char winner = board->checkWinner();
                if (winner != ' ') {
                    system("clear");  // Rensa skärmen igen när spelet är slut
                    board->printBoard();  // Skriv ut slutgiltiga brädan
                    setColor(winner == 'X' ? 34 : 31);  // Sätt färg till vinnaren (X = blå, O = röd)
                    cout << "Player " << (winner == 'X' ? "1" : "2") << " wins!\n";
                    resetColor();
                    gameOver = true;
                } else if (board->isFull()) {
                    // Kontrollera om det är oavgjort
                    system("clear");  // Rensa skärmen innan vi skriver ut den slutgiltiga brädan
                    board->printBoard();
                    cout << "It's a draw!\n";
                    gameOver = true;
                }
                // Byt spelare
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
    }

private:
    char currentPlayer;
    bool gameOver;
    Board* board;  // Objekt för brädan

    // Funktion för att sätta färgen med ANSI escape-koder
    void setColor(int color) {
        cout << "\033[" << color << "m";
    }

    // Funktion för att återställa färgen till standard
    void resetColor() {
        cout << "\033[0m";
    }
};

int main() {
    Game game;  // Skapa ett spelobjekt
    game.start();  // Starta spelet

    return 0;
}
