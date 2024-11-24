#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <unistd.h> // For sleep function

using namespace std;

class Board {
private:
    char spaces[9];

    bool checkLine(int a, int b, int c, char player) {
        return (spaces[a] == player && spaces[a] == spaces[b] && spaces[a] == spaces[c]);
    }

public:
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
            mvprintw(i / 3 * 2, (i % 3) * 4, " %c ", spaces[i]);
            if (i == cursorPos) {
                attroff(A_REVERSE);
            }
            if (i % 3 != 2) {
                mvprintw(i / 3 * 2, (i % 3) * 4 + 3, "|");
            }
            if (i / 3 != 2 && i % 3 == 2) {
                mvprintw(i / 3 * 2 + 1, 0, "---+---+---");
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

    bool checkWinner(char player) {
        return (checkLine(0, 1, 2, player) || checkLine(3, 4, 5, player) || checkLine(6, 7, 8, player) ||
                checkLine(0, 3, 6, player) || checkLine(1, 4, 7, player) || checkLine(2, 5, 8, player) ||
                checkLine(0, 4, 8, player) || checkLine(2, 4, 6, player));
    }

    bool checkTie() {
        return isBoardFull();
    }

    void updateSpace(int index, char marker) {
        spaces[index] = marker;
    }

    char getSpace(int index) {
        return spaces[index];
    }
};

class Player {
public:
    char marker;
    virtual void makeMove(Board& board, int& cursorPos) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(char m) { marker = m; }

    void makeMove(Board& board, int& cursorPos) override {
        int ch;
        while (true) {
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
                    if (board.getSpace(cursorPos) == ' ') {
                        board.updateSpace(cursorPos, marker);
                        return;
                    }
                    break;
            }
            board.drawBoard(cursorPos);
        }
    }
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(char m) { marker = m; }

    void makeMove(Board& board, int& cursorPos) override {
        int number;
        srand(time(0));

        while (true) {
            number = rand() % 9;
            if (board.getSpace(number) == ' ') {
                board.updateSpace(number, marker);
                break;
            }
        }
    }
};

class Game {
public:
    Board board;
    Player* player1;
    Player* player2;
    int cursorPos;

    Game(Player* p1, Player* p2) : player1(p1), player2(p2), cursorPos(0) {}

    void run() {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);

        while (true) {
            board = Board();
            cursorPos = 0;
            board.drawBoard(cursorPos);

            while (true) {
                player1->makeMove(board, cursorPos);
                board.drawBoard(cursorPos);
                if (board.checkWinner(player1->marker)) {
                    printw("Congratulations!!! You won!\n");
                    refresh();
                    sleep(1); 
                    endwin();
                    exit(0);
                }

                if (board.checkTie()) {
                    printw("It's a tie!\n");
                    refresh();
                    sleep(1); 
                    endwin();
                    exit(0);
                }

                player2->makeMove(board, cursorPos);
                board.drawBoard(cursorPos);
                if (board.checkWinner(player2->marker)) {
                    printw("You lose!!!\n");
                    refresh();
                    sleep(1); 
                    endwin();
                    exit(0);
                }

                if (board.checkTie()) {
                    printw("It's a tie!\n");
                    refresh();
                    sleep(1); 
                    endwin();
                    exit(0);
                }
            }
        }
    }
};

int main() {
    HumanPlayer human('X');
    ComputerPlayer computer('O');
    Game game(&human, &computer);
    game.run();
    return 0;
}
