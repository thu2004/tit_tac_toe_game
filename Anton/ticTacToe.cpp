#include <iostream>
#include <vector>

// Function declarations
void displayBoard(const char* board);
bool checkWin(const char* board, int activePlayer);
bool checkDraw(const char* board);
void playerMove(char* board, int activePlayer);
int nextPlayer(int activePlayer);

// Global ascii symbols

// clang-format off
  const std::vector<std::string> ASCII_X = {
    "   \\/",
    "   /\\"
  };
  const std::vector<std::string> ASCII_O = {
    "   __ ",
    "  |__|"

  };
  const std::vector<std::string> EMPTY = {
    "     ",
    "     "
  };
// clang-format on

int main() {
  // data
  char board[9] = {
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  };
  int activePlayer = 1;

  std::cout << "Welcome to Tic-Tac-Toe!\n";
  displayBoard(board);

  while (true) {
    playerMove(board, activePlayer);
    if (checkWin(board, activePlayer)) {
      switch (activePlayer) {
        case 1:
          std::cout << std::endl << std::endl;
          std::cout << "Player 1 (X) wins the game GG!" << std::endl;
          std::cout << std::endl << std::endl;
          std::cout << "Winning board: " << std::endl;        
          displayBoard(board);  
          break;
        case 2:
          std::cout << std::endl << std::endl;

          std::cout << "Player 2 (O) wins the game GG!" << std::endl;
          std::cout << std::endl << std::endl;
          std::cout << "Winning board: " << std::endl;
          displayBoard(board);
          break;
        default:
          break;
      }
      break;
    }
    if (checkDraw(board)) {
      std::cout << "It is a tie!" << std::endl;
      break;
    }
    activePlayer = nextPlayer(activePlayer);
    displayBoard(board);
  }
  std::cout << "\nPress Enter to exit...";
std::cin.ignore(1000, '\n');
std::cin.get();

  return 0;
}

// Function to display the game board

void displayBoard(const char* board) {
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
            std::cout << ASCII_X[line] << "   |";
            break;
          case 'O':
            std::cout << ASCII_O[line] << "  |";
            break;
          default:
            std::cout << EMPTY[line] << "   |";
            break;
        }
      }
      std::cout << std::endl;
    }
    std::cout << padding << "|________|________|________|\n";
  }
}

// Function to check if a player has won
bool checkWin(const char* board, int activePlayer) {
  char player = (activePlayer == 1) ? 'X' : 'O';

  // Horizontal win
  if ((board[0] == board[1] && board[1] == board[2] && board[0] == player) ||
      (board[3] == board[4] && board[4] == board[5] && board[3] == player) ||
      (board[6] == board[7] && board[7] == board[8] && board[6] == player)) {
    return true;
  }

  // Vertical win
  if ((board[0] == board[3] && board[3] == board[6] && board[0] == player) ||
      (board[1] == board[4] && board[4] == board[7] && board[1] == player) ||
      (board[2] == board[5] && board[5] == board[8] && board[2] == player)) {
    return true;
  }
  // Diagnoal win
  if ((board[0] == board[4] && board[4] == board[8] && board[0] == player) ||
      (board[2] == board[4] && board[4] == board[6] && board[2] == player)) {
    return true;
  }

  return false;
}

// Function to check if the game is a draw
bool checkDraw(const char* board) {
  for (int i = 0; i < 9; i++) {
    if (board[i] == ' ') return false;
  }
  return true;
}

// Function to let player make move
void playerMove(char* board, int activePlayer) {
  int choice = -1;

  std::cout << std::endl;
  if (activePlayer == 1)
    std::cout
        << "========================Player 1 (X)============================== "
        << std::endl;
  else
    std::cout
        << "========================Player 2 (O)============================== "
        << std::endl;
  do {
    std::cout << "Please make your move, where do you want to put your marker! "
                 "(1-9): ";
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > 9) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout << "That is not a square you can choose!" << std::endl;
      continue;
    }
    choice--;

    if (board[choice] != ' ') {
      std::cout << "That square is already taken, choose another one!"
                << std::endl;
    } else {
      break;
    }
  } while (true);
  switch (activePlayer) {
    case 1:
      board[choice] = 'X';
      break;
    case 2:
      board[choice] = 'O';
      break;
    default:
      break;
  }
}

// Function to switch player
int nextPlayer(int activePlayer) {
return (activePlayer == 1) ? 2 : 1;
}
