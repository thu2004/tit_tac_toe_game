#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

class TicTacToe {
private:
    std::vector<char> board; // Game board represented as a vector
    char currentPlayer;      // Tracks the current player ('X' or 'O')

    // Clears the console screen
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    // Checks if a move is valid
    bool isValidMove(int move) {
        return move >= 1 && move <= 9 && board[move - 1] == ' ';
    }

    // Checks if the current player has a winning combination
    bool checkWinningCondition(char player) {
        const std::vector<std::vector<int>> winLines = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
            {0, 4, 8}, {2, 4, 6}             // Diagonals
        };

        for (const auto& line : winLines) {
            if (board[line[0]] == player && 
                board[line[1]] == player && 
                board[line[2]] == player) {
                return true;
            }
        }
        return false;
    }

    // Checks if the board is full (for draw condition)
    bool isBoardFull() {
        for (char cell : board) {
            if (cell == ' ') return false;
        }
        return true;
    }

    // Adds colors to the player's marks for better visualization
    std::string coloredMark(char mark) {
        #ifdef _WIN32
            // No ANSI colors in Windows by default
            return std::string(1, mark);
        #else
            if (mark == 'X') return "\033[1;31mX\033[0m"; // Red for 'X'
            if (mark == 'O') return "\033[1;34mO\033[0m"; // Blue for 'O'
            return " "; // Empty cell
        #endif
    }

public:
    TicTacToe() : board(9, ' '), currentPlayer('X') {}

    // Displays the game board
    void displayBoard() {
        clearScreen();
        std::cout << "\n Tic-Tac-Toe Game\n\n";

        for (int i = 0; i < 9; ++i) {
            // Print cell number or player mark
            if (board[i] == ' ') {
                std::cout << " " << i + 1 << " ";
            } else {
                std::cout << " " << coloredMark(board[i]) << " ";
            }

            // Add grid separators
            if ((i + 1) % 3 != 0) {
                std::cout << "|";
            } else if (i < 8) {
                std::cout << "\n---+---+---\n";
            }
        }
        std::cout << "\n\n";
    }

    // The main game loop
    void play() {
        std::string input;
        int move;
        bool gameRunning = true;

        std::cout << "Welcome to Tic-Tac-Toe!\n";
        std::cout << "Enter 'q' or 'exit' at any time to quit the game.\n";

        while (gameRunning) {
            displayBoard();

            // Player input loop
            while (true) {
                std::cout << "Player " << coloredMark(currentPlayer) << ", enter your move (1-9): ";
                std::cin >> input;

                // Check for quit command
                if (input == "q" || input == "exit") {
                    std::cout << "Exiting the game. Thanks for playing!\n";
                    return;
                }

                // Convert input to integer
                try {
                    move = std::stoi(input);
                } catch (...) {
                    std::cout << "Invalid input. Please enter a number between 1 and 9.\n";
                    continue;
                }

                // Validate the move
                if (isValidMove(move)) {
                    board[move - 1] = currentPlayer;
                    break;
                } else {
                    std::cout << "Invalid move. Try again.\n";
                }
            }

            // Check game status
            if (checkWinningCondition(currentPlayer)) {
                displayBoard();
                std::cout << "Player " << coloredMark(currentPlayer) << " wins!\n";
                gameRunning = false;
            } else if (isBoardFull()) {
                displayBoard();
                std::cout << "It's a draw!\n";
                gameRunning = false;
            }

            // Switch players
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
