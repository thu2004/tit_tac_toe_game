#include <iostream>
#include <termios.h>
#include <unistd.h>

class Terminal
{
public:
    Terminal()
    {
        // Save the current terminal settings
        tcgetattr(STDIN_FILENO, &old_term);
        struct termios new_term = old_term;

        // Set the terminal to raw mode
        new_term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    }

    ~Terminal()
    {
        // Restore the original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    }

    char getch()
    {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        return ch;
    }

private:
    struct termios old_term;
};

class Board
{
public:
    char board[3][3] = {{'1', '2', '3'},
                        {'4', '5', '6'},
                        {'7', '8', '9'}};

    void displayBoard(int cursorRow, int cursorCol) // printar ut ett board
    { 
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (i == cursorRow && j == cursorCol)
                {
                    std::cout << "[" << board[i][j] << "]"; // highlighting
                }
                else
                {
                    std::cout << " " << board[i][j] << " "; // behövde en else statement, annars ville den inte funka
                }
            }
            std::cout << std::endl;
            if (i < 2)
            {
                std::cout << " --+--+--\n";
            }
        }
    }

    bool isPositionTaken(int row, int col)
    { 
        return board[row][col] == 'X' || board[row][col] == 'O'; //kollar om positionen är tagen
    }

    void placeMove(int row, int col, char player)
    { 
        board[row][col] = player; // X eller O in i rätt rowcolumn
    }

    bool checkWin(char player)
    {
        for (int i = 0; i < 3; ++i)
        {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // rows n columns
                (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            {
                return true;
            }
        }
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // diagonaler
            (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        {
            return true;
        }
        return false;
    }

    bool checkDraw()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            { 
                if (board[i][j] != 'X' && board[i][j] != 'O') // kollar om det är nånting på bordet som inte är fyllt
                {
                    return false;
                }
            }
        }
        return true;
    }
};

class Game
{
private:
    Board board;
    char currentPlayer;
    int cursorRow, cursorCol;

public:
    Game() : currentPlayer('X'), cursorRow(0), cursorCol(0) {} // konstruktor som initierar några värden 

    void switchPlayer()
    {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; //true false
    }

    void clear() // funkar inte på win, men går bra i linux tydligen
    {
#ifdef _WIN32
        system("cls"); 
#else
        system("clear");
#endif
        // for (int i = 0; i < 22; ++i) // clear for windows
        //     std::cout << std::endl;
    }

    void handleArrowKeys()
    {
        Terminal terminal;
        bool gameRunning = true;
        while (gameRunning)
        {
            board.displayBoard(cursorRow, cursorCol);

            char ch = terminal.getch(); // get char from console
            if (ch == '\033')  // kollar om det är en escape sequence,
            {                                
                char next = terminal.getch(); // om det är en arrow kommer den alltid skicka [ först
                if (next == '[')
                {
                    char arrow = terminal.getch(); // Följande A,B,C,D
                    switch (arrow)
                    {
                    case 'A': // Up arrow example '\033[A' <- up arrow
                        if (cursorRow > 0)
                            cursorRow--;
                        clear();
                        break;
                    case 'B': // Down arrow example '\033[B' <- down arrow
                        if (cursorRow < 2)
                            cursorRow++;
                        clear();
                        break;
                    case 'C': // Right arrow example '\033[C' <- right arrow
                        if (cursorCol < 2)
                            cursorCol++;
                        clear();
                        break;
                    case 'D': // Left arrow example '\033[D' <- left arrow
                        if (cursorCol > 0)
                            cursorCol--;
                        clear();
                        break;
                    }
                }
            }
            else if (ch == '\n') // om jag trycker enter
            { 
                clear();
                if (!board.isPositionTaken(cursorRow, cursorCol))
                {                                                         
                    board.placeMove(cursorRow, cursorCol, currentPlayer); 
                    if (board.checkWin(currentPlayer))
                    {
                        board.displayBoard(cursorRow, cursorCol);
                        std::cout << "spelare " << currentPlayer << " vinner!" << std::endl;
                        gameRunning = false;
                    }
                    else if (board.checkDraw())
                    {
                        board.displayBoard(cursorRow, cursorCol);
                        std::cout << "lika!" << std::endl;
                        gameRunning = false;
                    }
                    else
                    {
                        switchPlayer();
                    }
                }
            }
            else if (ch == 'q') // Quit the game on 'q'
            { 
                gameRunning = false;
            }
        }
    }

    void play()
    {
        std::cout << "Welcome to Tic-Tac-Toe!" << std::endl;
        std::cout << "Use arrow keys to move and Enter to place a move. Press 'q' to quit." << std::endl;
        handleArrowKeys();
    }
};

int main()
{
    Game game;
    game.play();
    return 0;
}
