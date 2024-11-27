#include <iostream>
#include <vector>
using namespace std;


class Board {
private:
    vector<char> cells;

public:
    // Constructor to initialize the board
    Board() : cells(9, ' ') {}

    // Method to display the board
    void display() const {
        cout << "\n";
        for (int i = 0; i < 9; i++) {
            cout << " " << (cells[i] == ' ' ? char('1' + i) : cells[i]) << " ";
            if (i % 3 != 2) cout << "|";
            else if (i != 8) cout << "\n---|---|---\n";
        }
        cout << "\n\n";
    }

    // Method to check if a cell is empty
    bool isEmpty(int index) const {
        return cells[index] == ' ';
    }

    // Method to set a cell's value
    void setCell(int index, char value) {
        cells[index] = value;
    }

    // Method to check if the current player has won
    bool checkWin(char player) const {
        const int winConditions[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
            {0, 4, 8}, {2, 4, 6}             // Diagonals
        };
        for (const auto& condition : winConditions) {
            if (cells[condition[0]] == player &&
                cells[condition[1]] == player &&
                cells[condition[2]] == player) {
                return true;
            }
        }
        return false;
    }

    // Method to check if the board is full (draw)
    bool isFull() const {
        for (const char& cell : cells) {
            if (cell == ' ') return false;
        }
        return true;
    }
};

// Game class: Manages the game flow and players
class Game {
private:
    Board board;
    char currentPlayer;

    // Switch to the other player
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Handle the player's turn
    void playerTurn() {
        int move;
        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> move;

            // Validate input and check if cell is empty
            if (move >= 1 && move <= 9 && board.isEmpty(move - 1)) {
                board.setCell(move - 1, currentPlayer);
                break;
            } else {
                cout << "Invalid move! Please choose an empty cell (1-9).\n";
            }
        }
    }

    // Check if the game is over
    bool isGameOver() const {
        if (board.checkWin(currentPlayer)) {
            board.display();
            cout << "Player " << currentPlayer << " wins!\n";
            return true;
        } else if (board.isFull()) {
            board.display();
            cout << "It's a draw!\n";
            return true;
        }
        return false;
    }

public:
    // Constructor to initialize the game
    Game() : currentPlayer('X') {}

    // Method to start the game loop
    void start() {
        cout << "Welcome to Tic-Tac-Toe!\n";
        while (true) {
            board.display();
            playerTurn();
            if (isGameOver()) break;
            switchPlayer();
        }
    }
};

// Main function
int main() {
    Game game;
    game.start();
    return 0;
}
