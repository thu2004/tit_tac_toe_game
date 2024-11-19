#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
bool checkWinner(char *spaces, char player, char computer);
bool checkTie(char *spaces);
bool checkLine(char *spaces, int a, int b, int c, char player);
bool isBoardFull(char *spaces);
bool playAgain();

int main() {
    bool running = true;
    while (running) {
        char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
        char player = 'X';
        char computer = 'O';
        bool gameRunning = true;
        drawBoard(spaces);

        while (gameRunning) {
            playerMove(spaces, player);
            drawBoard(spaces);
            if (checkWinner(spaces, player, computer)) {
                gameRunning = false;
                break;
            } else if (checkTie(spaces)) {
                gameRunning = false;
                break;
            }
            computerMove(spaces, computer);
            drawBoard(spaces);
            if (checkWinner(spaces, player, computer)) {
                gameRunning = false;
                break;
            } else if (checkTie(spaces)) {
                gameRunning = false;
                break;
            }
        }
        cout << "Thanks for playing!\n";
        running = playAgain();
    }
    return 0;
}

void drawBoard(char *spaces) {
    cout << '\n';
    cout << "     |     |     " << '\n';
    cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  " << '\n';
    cout << "_____|_____|_____" << '\n';
    cout << "     |     |     " << '\n';
    cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  " << '\n';
    cout << "_____|_____|_____" << '\n';
    cout << "     |     |     " << '\n';
    cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  " << '\n';
    cout << "     |     |     " << '\n';
    cout << '\n';
}

void playerMove(char *spaces, char player) {
    int number;
    if (isBoardFull(spaces)) {
        cout << "No empty spots left. It's a tie!\n";
        return;
    }
    while (true) {
        cout << "Enter a spot to place a marker (1-9): ";
        cin >> number;
        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
        } else if (number < 1 || number > 9) {
            cout << "Invalid number. Please enter a number between 1 and 9.\n";
        } else if (spaces[number - 1] != ' ') {
            cout << "Spot taken, try another spot.\n";
        } else {
            spaces[number - 1] = player;
            break;
        }
    }
}

void computerMove(char *spaces, char computer) {
    int number;
    srand(time(0));

    while (true) {
        number = rand() % 9;
        if (spaces[number] == ' ') {
            spaces[number] = computer;
            break;
        }
    }
}

bool checkLine(char *spaces, int a, int b, int c, char player) {
    return (spaces[a] == player && spaces[a] == spaces[b] && spaces[a] == spaces[c]);
}

bool checkWinner(char *spaces, char player, char computer) {
    // Check rows, columns, and diagonals for player
    if (checkLine(spaces, 0, 1, 2, player) || checkLine(spaces, 3, 4, 5, player) || checkLine(spaces, 6, 7, 8, player) ||
        checkLine(spaces, 0, 3, 6, player) || checkLine(spaces, 1, 4, 7, player) || checkLine(spaces, 2, 5, 8, player) ||
        checkLine(spaces, 0, 4, 8, player) || checkLine(spaces, 2, 4, 6, player)) {
        cout << "CONGRATULATIONS!!! YOU WIN!\n";
        return true;
    }
    // Check rows, columns, and diagonals for computer
    if (checkLine(spaces, 0, 1, 2, computer) || checkLine(spaces, 3, 4, 5, computer) || checkLine(spaces, 6, 7, 8, computer) ||
        checkLine(spaces, 0, 3, 6, computer) || checkLine(spaces, 1, 4, 7, computer) || checkLine(spaces, 2, 5, 8, computer) ||
        checkLine(spaces, 0, 4, 8, computer) || checkLine(spaces, 2, 4, 6, computer)) {
        cout << "SORRY! YOU LOSE, BETTER LUCK NEXT TIME!\n";
        return true;
    }
    return false;
}

bool checkTie(char *spaces) {
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            return false;
        }
    }
    cout << "IT'S A TIE, BUT NEVER GIVE UP!\n";
    return true;
}

bool isBoardFull(char *spaces) {
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            return false;
        }
    }
    return true;
}

bool playAgain() {
    char choice;
    while (true) {
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }
}
