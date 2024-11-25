#include <iostream>
#include <vector>
#include <cstdlib>

class Board {
private:
    std::vector<char> board;
    int size;

public:
    Board(int size) : size(size), board(size * size, ' ') {}

    void display(int cursorPosition) {
        std::system("clear"); // Clear screen
        for (int i = 0; i < size * size; ++i) {
            if (board[i] == ' ') {
                if (i == cursorPosition) {
                    std::cout << "\033[1;32m" << " " << i + 1 << " " << "\033[0m"; // Highlight cursor position
                } else {
                    std::cout << " " << i + 1 << " ";
                }
            } else {
                std::cout << " " << board[i] << " ";
            }
            if ((i + 1) % size != 0) {
                std::cout << "|";
            } else if (i < size * size - 1) {
                std::cout << "\n";
                for (int j = 0; j < size; ++j) {
                    std::cout << "---";
                    if (j < size - 1) std::cout << "+";
                }
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }

    bool isValidMove(int move) {
        return move >= 1 && move <= size * size && board[move - 1] == ' ';
    }

    bool placeMark(int move, char mark) {
        if (isValidMove(move)) {
            board[move - 1] = mark;
            return true;
        }
        return false;
    }

    bool checkWin(char mark) {
        const std::vector<std::vector<int>> winLines = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
            {0, 4, 8}, {2, 4, 6}             // Diagonals
        };

        for (const auto& line : winLines) {
            if (board[line[0]] == mark && board[line[1]] == mark && board[line[2]] == mark) {
                return true;
            }
        }
        return false;
    }

    bool isFull() {
        for (char cell : board) {
            if (cell == ' ') return false;
        }
        return true;
    }
};

class Game {
private:
    Board board;
    char currentPlayer;
    int cursorPosition;

public:
    Game() : board(3), currentPlayer('X'), cursorPosition(0) {}

    void run() {
        std::cout << "Welcome to Tic-Tac-Toe!\n";
        play();
    }

    void play() {
        bool gameRunning = true;

        while (gameRunning) {
            board.display(cursorPosition);

            while (true) {
                char input;
                std::cout << "Player " << currentPlayer << ", use 'w', 'a', 's', 'd' to move, and 'e' to select:\n";
                std::cin >> input;

                if (input == 'w') { // Move cursor up
                    if (cursorPosition >= 3) cursorPosition -= 3;
                } else if (input == 's') { // Move cursor down
                    if (cursorPosition < 6) cursorPosition += 3;
                } else if (input == 'a') { // Move cursor left
                    if (cursorPosition % 3 != 0) cursorPosition--;
                } else if (input == 'd') { // Move cursor right
                    if (cursorPosition % 3 != 2) cursorPosition++;
                } else if (input == 'e') { // Select the current cell
                    if (board.placeMark(cursorPosition + 1, currentPlayer)) {
                        break;
                    } else {
                        std::cout << "Invalid move. Cell already taken. Try again.\n";
                    }
                } else {
                    std::cout << "Invalid input. Use 'w', 'a', 's', 'd' to move, and 'e' to select.\n";
                }
                board.display(cursorPosition);
            }

            if (board.checkWin(currentPlayer)) {
                board.display(cursorPosition);
                std::cout << "Player " << currentPlayer << " wins!\n";
                gameRunning = false;
            } else if (board.isFull()) {
                board.display(cursorPosition);
                std::cout << "It's a draw!\n";
                gameRunning = false;
            }

            switchPlayer();
        }
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
