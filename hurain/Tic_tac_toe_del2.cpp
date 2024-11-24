#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

class Board {
public:
    char spaces[9];

    Board() {
        for (int i = 0; i < 9; i++) {
            spaces[i] = ' ';
        }
    }

    void drawBoard() {
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

    bool isBoardFull() {
        for (int i = 0; i < 9; i++) {
            if (spaces[i] == ' ') {
                return false;
            }
        }
        return true;
    }

    bool checkLine(int a, int b, int c, char player) {
        return (spaces[a] == player && spaces[a] == spaces[b] && spaces[a] == spaces[c]);
    }

    bool checkWinner(char player) {
        return (checkLine(0, 1, 2, player) || checkLine(3, 4, 5, player) || checkLine(6, 7, 8, player) ||
                checkLine(0, 3, 6, player) || checkLine(1, 4, 7, player) || checkLine(2, 5, 8, player) ||
                checkLine(0, 4, 8, player) || checkLine(2, 4, 6, player));
    }

    bool checkTie() {
        if (isBoardFull()) {
            cout << "It's a tie!\n";
            return true;
        }
        return false;
    }
};

class Game {
public:
    char player;
    char computer;
    Board board;

    Game() : player('X'), computer('O') {}

    void playerMove() {
        int number;
        if (board.isBoardFull()) {
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
            } else if (board.spaces[number - 1] != ' ') {
                cout << "Spot taken, try another spot.\n";
            } else {
                board.spaces[number - 1] = player;
                break;
            }
        }
    }

    void computerMove() {
        int number;
        srand(time(0));

        while (true) {
            number = rand() % 9;
            if (board.spaces[number] == ' ') {
                board.spaces[number] = computer;
                break;
            }
        }
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

    void run() {
        bool running = true;
        while (running) {
            board = Board();
            bool gameRunning = true;
            board.drawBoard();

            while (gameRunning) {
                playerMove();
                board.drawBoard();
                if (board.checkWinner(player)) {
                    cout << "CONGRATULATIONS!!! YOU WIN!\n";
                    gameRunning = false;
                    break;
                } else if (board.checkTie()) {
                    gameRunning = false;
                    break;
                }
                computerMove();
                board.drawBoard();
                if (board.checkWinner(computer)) {
                    cout << "COMPUTER WINS! BETTER LUCK NEXT TIME!\n";
                    gameRunning = false;
                    break;
                } else if (board.checkTie()) {
                    gameRunning = false;
                    break;
                }
            }
            cout << "Thanks for playing!\n";
            running = playAgain();
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
