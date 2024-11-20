#include <iostream>
#include <vector>

struct AsciiSymbols {
  // clang-format off
  const std::vector<std::string> x = { //BYT NAMN
    "   \\/",
    "   /\\"
  };
  const std::vector<std::string> o = {
    "   __ ",
    "  |__|"

  };
  const std::vector<std::string> empty = {
      "     ", 
      "     "
  };
  // clang-format on
};

class Board {
 private:
  // Private Data
  AsciiSymbols symbols;
  char board[9] = {
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  };

 public:
  // Public Functions.
  void displayBoard() {
    std::string padding = "              ";
    std::cout << padding << "____________________________\n";
    for (int row = 0; row < 3; row++) {
      std::cout << padding << "|";
      for (int column = 0; column < 3; column++) {
        int i = row * 3 + column;
        std::cout << i + 1 << "       |";
      }
      std::cout << std::endl;

      for (int line = 0; line < 2; line++) {
        std::cout << padding << "|";
        for (int column = 0; column < 3; column++) {
          int i = row * 3 + column;
          switch (board[i]) {
            case 'X':
              std::cout << symbols.x[line] << "   |";
              break;
            case 'O':
              std::cout << symbols.o[line] << "  |";
              break;
            default:
              std::cout << symbols.empty[line] << "   |";
              break;
          }
        }
        std::cout << std::endl;
      }
      std::cout << padding << "|________|________|________|\n";
    }
  }
  char getCell(int index) const { return board[index]; }
  void setCell(int index, char value) { board[index] = value; }
  bool isCellEmpty(int index) const { return board[index] == ' '; }
};
class Game {
 private:
  // Data
  int activePlayer = 1;
  Board gameBoard;

  // Private  Functions
  bool checkWin() {
    char player = (activePlayer == 1) ? 'X' : 'O';

    // Horizontal win
    if ((gameBoard.getCell(0) == gameBoard.getCell(1) &&
         gameBoard.getCell(1) == gameBoard.getCell(2) &&
         gameBoard.getCell(0) == player) ||
        (gameBoard.getCell(3) == gameBoard.getCell(4) &&
         gameBoard.getCell(4) == gameBoard.getCell(5) &&
         gameBoard.getCell(3) == player) ||
        (gameBoard.getCell(6) == gameBoard.getCell(7) &&
         gameBoard.getCell(7) == gameBoard.getCell(8) &&
         gameBoard.getCell(6) == player)) {
      return true;
    }

    // Vertical win
    if ((gameBoard.getCell(0) == gameBoard.getCell(3) &&
         gameBoard.getCell(3) == gameBoard.getCell(6) &&
         gameBoard.getCell(0) == player) ||
        (gameBoard.getCell(1) == gameBoard.getCell(4) &&
         gameBoard.getCell(4) == gameBoard.getCell(7) &&
         gameBoard.getCell(1) == player) ||
        (gameBoard.getCell(2) == gameBoard.getCell(5) &&
         gameBoard.getCell(5) == gameBoard.getCell(8) &&
         gameBoard.getCell(2) == player)) {
      return true;
    }
    // Diagnoal win
    if ((gameBoard.getCell(0) == gameBoard.getCell(4) &&
         gameBoard.getCell(4) == gameBoard.getCell(8) &&
         gameBoard.getCell(0) == player) ||
        (gameBoard.getCell(2) == gameBoard.getCell(4) &&
         gameBoard.getCell(4) == gameBoard.getCell(6) &&
         gameBoard.getCell(2) == player)) {
      return true;
    }

    return false;
  }
  bool checkDraw() {
    for (int i = 0; i < 9; i++) {
      if (gameBoard.isCellEmpty(i)) return false;
    }
    return true;
  }
  void nextPlayer() { activePlayer = (activePlayer == 1) ? 2 : 1; }
  void playerMove() {
    int choice = -1;
    bool moveMade = false;

    std::cout << std::endl;
    if (activePlayer == 1)
      std::cout << "========================Player 1 "
                   "(X)============================== "
                << std::endl;
    else
      std::cout << "========================Player 2 "
                   "(O)============================== "
                << std::endl;
    do {
      std::cout
          << "Please make your move, where do you want to put your marker? "
             "(1-9): ";
      std::cin >> choice;

      if (std::cin.fail() || choice < 1 || choice > 9) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "That is not a square you can choose!" << std::endl;
        continue;
      }
      choice--;

      if (!gameBoard.isCellEmpty(choice)) {
        std::cout << "That square is already taken, choose another one!"
                  << std::endl;
      } else {
        moveMade = true;
      }
    } while (!moveMade);

    switch (activePlayer) {
      case 1:
        gameBoard.setCell(choice, 'X');
        break;
      case 2:
        gameBoard.setCell(choice, 'O');
        break;
      default:
        break;
    }
  }

 public:
  // Public  Functions
  void play() {
    std::cout << "Welcome to Tic-Tac-Toe!\n";
    gameBoard.displayBoard();

    while (true) {
      playerMove();
      if (checkWin()) {
        switch (activePlayer) {
          case 1:
            std::cout << std::endl << std::endl;
            std::cout << "Player 1 (X) wins the game GG!" << std::endl;
            std::cout << std::endl << std::endl;
            std::cout << "Winning board: " << std::endl;
            gameBoard.displayBoard();
            break;
          case 2:
            std::cout << std::endl << std::endl;

            std::cout << "Player 2 (O) wins the game GG!" << std::endl;
            std::cout << std::endl << std::endl;
            std::cout << "Winning board: " << std::endl;
            gameBoard.displayBoard();
          default:
            break;
        }
        break;
      }
      if (checkDraw()) {
        std::cout << "It is a tie!" << std::endl;
        break;
      }
      nextPlayer();
      gameBoard.displayBoard();
    }
    std::cout << "\nPress Enter to exit...";
    std::cin.ignore(1000, '\n');
    std::cin.get();
  }
};

int main() {
  Game game;
  game.play();
  return 0;
}