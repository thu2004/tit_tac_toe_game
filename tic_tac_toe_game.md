## 1. Create a Tic-Tac-Toe game run in a console

Here is the pseudocode for the Tic-Tac-Toe game:

1. **Initialize Game State**:
    
    * Create a 3x3 board filled with empty spaces.
    * Define two players, 'X' and 'O'.
    * Set the initial player turn to 0.
    * Set the initial cursor position to the top-left corner of the board (0, 0).
2. **Game Loop**:
    
    * Repeat the following steps until the game ends:
        1. **Print Board**:
            * Clear the console.
            * Loop through each cell of the board and print its value.
            * Highlight the current cursor position.
        2. **Handle Player Input**:
            * Display whose turn it is.
            * Wait for player input:
                * If user enter number 1-9 
                    * If the selected cell is empty, break out of the input loop.
                    * If the selected cell is not empty, prompt the player to choose another cell.
                    
        3. **Place Player Mark**:
            * Set the current player's mark ('X' or 'O') in the selected cell.
        4. **Check for Win or Draw**:
            * If the current player has won, display a winning message and end the game.
            * If the board is full and no player has won, display a draw message and end the game.
        5. **Switch Turn**:
            * Switch to the other player.
3. **End of Game**:
    
    * The game loop ends when either a player wins or the game ends in a draw.


```cpp
#include <iostream>
using namespace std;

// Function declarations
void displayBoard(...);
bool checkWin(...);
bool checkDraw(...);

int main() {
    // data
    bool gameRunning = true;

    cout << "Welcome to Tic-Tac-Toe!\n";

    while (gameRunning) {
        displayBoard(board);
        ...
    }

    return 0;
}

// Function to display the game board
void displayBoard(...) {
    
}

// Function to check if a player has won
bool checkWin(...) {
    
}

// Function to check if the game is a draw
bool checkDraw(...) {
}
```

### Example Output:

```diff
Welcome to Tic-Tac-Toe!

 1 | 2 | 3 
---|---|---
 4 | 5 | 6 
---|---|---
 7 | 8 | 9 

Player X, enter your move (1-9): 5

 1 | 2 | 3 
---|---|---
 4 | X | 6 
---|---|---
 7 | 8 | 9 

Player O, enter your move (1-9): 1
...
```

## 2. Refactory the game using Object Oriented Programming.

Create Game and Board class and define the attributes and methods. Rewrite the main function.

## 3. Extent the game to handle player input with arrow keys. 

Run the game for linux. using WSL (Windows machine)

1. **Handle Player Input**:
    * Wait for player input:
        * If **Arrow Up** is pressed, move the cursor up (if possible).
        * If **Arrow Down** is pressed, move the cursor down (if possible).
        * If **Arrow Right** is pressed, move the cursor right (if possible).
        * If **Arrow Left** is pressed, move the cursor left (if possible).
        * If **Enter** is pressed:
            * If the selected cell is empty, break out of the input loop.
            * If the selected cell is not empty, prompt the player to choose another cell.

Here is example how to get the Arrow work in Linux / WSL

https://github.com/thu2004/cpp_kurs_1/blob/main/arrow_test.cpp