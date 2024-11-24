#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

class Board {
private:
    std::vector<char> board;
    int size;

public:
    Board(int size) : size(size), board(size * size, ' ') {}

    void display() {
        for (int i = 0; i < size * size; ++i) {
            if (board[i] == ' ') {
                std::cout << " " << i + 1 << " ";
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

public:
    Game() : board(3), currentPlayer('X') {}

    void play() {
        std::string input;
        int move;
        bool gameRunning = true;

        std::cout << "Welcome to Tic-Tac-Toe!\n";

        while (gameRunning) {
            board.display();

            while (true) {
                std::cout << "Player " << currentPlayer << ", enter your move (1-9): ";
                std::cin >> input;

                if (input == "q" || input == "exit") {
                    std::cout << "Exiting the game. Thanks for playing!\n";
                    return;
                }

                try {
                    move = std::stoi(input);
                } catch (...) {
                    std::cout << "Invalid input. Please enter a number between 1 and 9.\n";
                    continue;
                }

                if (board.placeMark(move, currentPlayer)) {
                    break;
                } else {
                    std::cout << "Invalid move. Try again.\n";
                }
            }

            if (board.checkWin(currentPlayer)) {
                board.display();
                std::cout << "Player " << currentPlayer << " wins!\n";
                gameRunning = false;
            } else if (board.isFull()) {
                board.display();
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
    game.play();
    return 0;
}