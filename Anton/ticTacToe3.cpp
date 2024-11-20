#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <vector>

struct AsciiSymbols {
  // clang-format off
  const std::vector<std::string> x = { 
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
  const std::vector<std::string> cursorRedX = { 
    "\033[31m   \\/\033[0m",
    "\033[31m   /\\\033[0m"
  };
  const std::vector<std::string> cursorRedO = {
    "\033[31m  __ \033[0m",
    "\033[31m |__|\033[0m"

  };
    const std::vector<std::string> cursorGreenX = { 
    "\033[32m   \\/\033[0m",
    "\033[32m   /\\\033[0m"
  };
  const std::vector<std::string> cursorGreenO = {
    "\033[32m  __ \033[0m",
    "\033[32m |__|\033[0m"

  };

  // clang-format on
};

// Class handles terminal manipulation
class Terminal {
 public:
  // Constructor
  Terminal() {
    // Save old terminal atribuytes to old_term and copy to new_term
    tcgetattr(STDERR_FILENO, &old_term);
    struct termios new_term = old_term;

    // Set the terminal to raw mode in new_term
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDERR_FILENO, TCSANOW, &new_term);
  }

  // Deconstructor
  ~Terminal() { tcsetattr(STDIN_FILENO, TCSANOW, &old_term); }

  // Read input without waiting for Enter.
  char getch() {
    char ch;
    read(STDERR_FILENO, &ch, 1);
    return ch;
  }

 private:
  struct termios old_term;
};

// Class handles state of board.
class Board {
 private:
  // Private Data
  AsciiSymbols symbols;
  char board[9] = {
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  };

 public:
  // Public Functions.
  void displayBoard(const int cursorX, const int cursorY,
                    const int& activePlayer) {
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
          if (row == cursorY && column == cursorX) {
            if (board[i] == ' ') {
              if (activePlayer == 1) {
                std::cout << symbols.cursorGreenX[line] << "   |";
              } else {
                std::cout << symbols.cursorGreenO[line] << "   |";
              }
            } else {
              if (activePlayer == 1) {
                std::cout << symbols.cursorRedX[line] << "   |";
              } else {
                std::cout << symbols.cursorRedO[line] << "   |";
              }
            }
          } else {
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

// Class handles flow of game.
class Game {
 private:
  // Data
  int activePlayer = 1;
  Board gameBoard;
  bool quitGame = false;

  // Private  Functions
  void handleArrowKey(char key, int& cursorX, int& cursorY) {
    switch (key) {
      case 'A':
        if (cursorY > 0) cursorY--;
        break;
      case 'B':
        if (cursorY < 2) cursorY++;
        break;
      case 'C':
        if (cursorX < 2) cursorX++;
        break;
      case 'D':
        if (cursorX > 0) cursorX--;
    }
  }
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
    int cursorX = 0, cursorY = 0;
    bool moveMade = false;

    while (!moveMade) {
      system("clear");
      std::cout << "It is Player " << activePlayer << "'s turn:" << std::endl;
      gameBoard.displayBoard(cursorX, cursorY, activePlayer);

      Terminal terminal;
      char key = terminal.getch();
      if (key == 'Q' || key == 'q') {
        quitGame = true;
        return;
      }
      if (key == '\033') {
        terminal.getch();
        char arrow = terminal.getch();
        handleArrowKey(arrow, cursorX, cursorY);
      } else if (key == '\n') {
        int index = cursorY * 3 + cursorX;
        if (gameBoard.isCellEmpty(index)) {
          gameBoard.setCell(index, activePlayer == 1 ? 'X' : 'O');
          moveMade = true;
        }
      }
    }
  }

 public:
  // Public  Functions
  void play() {
    bool gameRunning = true;
    system("clear");
    std::cout << "Welcome to Anton's TiCety TaCety ToeSy!\n\n"
                 "How to play:\nMove your cursor (X for player 1 and O for "
                 "player 2).\n"
                 "When your cursor is green you can place your marker by "
                 "pressing ENTER.\n"
                 "If your cursor is red it means the cell is already taken.\n"
                 "First player to reach 3 vertical, horizontal or diagnal "
                 "markers wins the game.\n\n"
                 "You can quit the game any time by pressing 'Q'\n\n"
                 "Press ENTER to begin, good luck!"
              << std::endl;
    std::cin.get();

    while (gameRunning) {
      playerMove();
      if (quitGame) {
        std::cout << std::endl << std::endl;
        std::cout << "Player " << activePlayer << " has stopped the game."
                  << std::endl;
        std::cout << std::endl << std::endl;
        gameRunning = false;
      }
      if (checkWin()) {
        std::cout << std::endl << std::endl;
        std::cout << "Player " << activePlayer << " wins the game GG!"
                  << std::endl;
        std::cout << std::endl << std::endl;
        gameRunning = false;
      }
      if (checkDraw()) {
        std::cout << "It is a tie!" << std::endl;
        gameRunning = false;
      }
      nextPlayer();
    }
  }
};

int main() {
  Game game;
  game.play();
  return 0;
}