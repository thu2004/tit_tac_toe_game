#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

using namespace std;

class Board {
public:
    char spaces[9];

    Board() {
        for (int i = 0; i < 9; i++) {
            spaces[i] = ' ';
        }
    }

    void drawBoard(int cursorPos) {
        clear();
        for (int i = 0; i < 9; i++) {
            if (i == cursorPos) {
                attron(A_REVERSE);
            }
            printw(" %c ", spaces[i]);
            if (i == cursorPos) {
                attroff(A_REVERSE);
            }
            if ((i + 1) % 3 == 0) {
                printw("\n");
            } else {
                printw("|");
            }
        }
        refresh();
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
            printw("It's a tie!\n");
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
    int cursorPos;

    Game() : player('X'), computer('O'), cursorPos(0) {}

    void playerMove() {
        int ch;
        while (true) {
            board.drawBoard(cursorPos);
            ch = getch();
            switch (ch) {
                case KEY_UP:
                    if (cursorPos >= 3) cursorPos -= 3;
                    break;
                case KEY_DOWN:
                    if (cursorPos <= 5) cursorPos += 3;
                    break;
                case KEY_LEFT:
                    if (cursorPos % 3 != 0) cursorPos -= 1;
                    break;
                case KEY_RIGHT:
                    if (cursorPos % 3 != 2) cursorPos += 1;
                    break;
                case '\n':
                case KEY_ENTER:
                    if (board.spaces[cursorPos] == ' ') {
                        board.spaces[cursorPos] = player;
                        return;
                    } else {
                        printw("Spot taken, try another spot.\n");
                        refresh();
                        napms(1000);
                    }
                    break;
                default:
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
            printw("Do you want to play again? (y/n): ");
            refresh();
            choice = getch();
            if (choice == 'y' || choice == 'Y') {
                return true;
            } else if (choice == 'n' || choice == 'N') {
                return false;
            } else {
                printw("Invalid input. Please enter 'y' or 'n'.\n");
                refresh();
                napms(1000);
            }
        }
    }

    void run() {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);

        bool running = true;
        while (running) {
            board = Board();
            cursorPos = 0;
            bool gameRunning = true;
            board.drawBoard(cursorPos);

            while (gameRunning) {
                playerMove();
                board.drawBoard(cursorPos);
                if (board.checkWinner(player)) {
                    printw("CONGRATULATIONS!!! YOU WIN!\n");
                    gameRunning = false;
                } else if (board.checkTie()) {
                    gameRunning = false;
                } else {
                    computerMove();
                    board.drawBoard(cursorPos);
                    if (board.checkWinner(computer)) {
                        printw("COMPUTER WINS! BETTER LUCK NEXT TIME!\n");
                        gameRunning = false;
                    } else if (board.checkTie()) {
                        gameRunning = false;
                    }
                }
            }
            printw("Thanks for playing!\n");
            running = playAgain();
        }

        endwin();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
