/*

Hej Chi Thu! 
Thaks for playing my game. I have a question.
den sista val precis innan man vinner förändras inte till 
'X' eller 'O' utan default nummeret i arreyen visas kvar. 
Frågan är att hur man gör för att den sista valet förändras 
till 'X' eller 'O'. Hör gärna av dig. Mvh.Ayumi"

*/

#include <iostream>
#include <termios.h>
#include <unistd.h>

class Terminal {
public:
    Terminal() {
        // Save the current terminal settings
        tcgetattr(STDIN_FILENO, &old_term);
        struct termios new_term = old_term;

        // Set the terminal to raw mode
        new_term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    }

    ~Terminal() {
        // Restore the original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    }

    char getch() {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        return ch;
    }

private:
    struct termios old_term;
};





class Board {
public:
    char board[3][3] = {{'1', '2', '3'}, {'4', '5','6'}, {'7', '8', '9'}};

    void drawBoard(){
        
    std::cout << '\n';
    std::cout << "     |     |     " << '\n';
    std::cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << '\n';
    std::cout << '\n';
    }

};

class Game
{
public:
    Board board;
    bool running = true;

    char player = 'X';
    
    int row; 
    int column;

    Terminal terminal;

    void handleArrowKeys() {
        // initial values: the center of the board: the first place of user
        int row = 1; 
        int column = 1;

        while (running) {
            char ch = terminal.getch(); // Get a character from the console
            if (ch == '\n') {
                break;
            }      
            if (ch == '\033') { // Escape sequence
                char next = terminal.getch(); // Get the next character
                if (next == '[') {
                    char arrow = terminal.getch(); // Get the actual arrow key code
                    switch (arrow) {
                        case 'A': // Up arrow //board[row][column]
                            std::cout << "Up arrow pressed" << std::endl;
                            if(row > 0 && row <= 2) {row --;}
                            break;
                        case 'B': // Down arrow
                            std::cout << "Down arrow pressed" << std::endl;
                            if(row >= 0 && row < 2){row ++;}
                            break;
                        case 'C': // Right arrow
                            std::cout << "Right arrow pressed" << std::endl;
                            if(column >= 0 && column < 2){column ++;}
                            break;
                        case 'D': // Left arrow
                            std::cout << "Left arrow pressed" << std::endl;
                            if(column > 0 && column <= 2) {column --;}
                            break;
                        default:
                            std::cout << "Invaried input!\n";
                            break;
                    } 
                }       
            } else {
                // Handle other keys (e.g., exit on 'q')
                if (ch == 'q') {
                    std::cout << "You quited.\n";
                    running = false;
                    break; // Exit the loop
                } else {
                    std::cout << "Key pressed: " << ch << std::endl;
                }
            }
            
        }

        // fill in player's choce
        
        if (player == 'X' && board.board[row][column] != 'X' && board.board[row][column] != 'O'){
            board.board[row][column] = 'X';
        

        } else if (player == 'O' && board.board[row][column]!= 'X' && board.board[row][column] != 'O'){
            board.board[row][column] = 'O';
        

        } else if (board.board[row][column]== 'X' && board.board[row][column] == 'O') {
            std::cout << " Box already filled! Please try again! \n";
            handleArrowKeys();
        }        
    }


    
    bool checkWinner()
    {   
        // loop 1-3
        for(int i = 0; i < 3; ++i)
        {
            if ((board.board[i][0] == player && board.board[i][1] == player && board.board[i][2] == player) || // Row check
                (board.board[0][i] == player && board.board[1][i] == player && board.board[2][i] == player)) // column
            {
                return true;
            }
        
            if ((board.board[0][0] == player && board.board[1][1] == player && board.board[2][2] == player) || // Diagonal check
                (board.board[0][2] == player && board.board[1][1] == player && board.board[2][0] == player))
            {
                return true;
            }
        }
        return false;
    }

    bool checkTie() 
    {
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                if (board.board[i][j] != 'X' && board.board[i][j] != 'O') 
                {
                    return false; // check the empty space left on the board
                }
            }
        }
        return true;
    }


    void playGame()
    {
        while(running){

            // intro
            std::cout << "Tic Tac Toe Game \n";
            std::cout << "Player1[X] Player2[O] Quit(q)\n";
            std::cout << "Press arrow keys (up, down, left, right) or 'q' to quit." << std::endl;
            std::cout << "The initial location is the center \n";
            
            board.drawBoard();
            handleArrowKeys();

            if(checkWinner()){
                std::cout << "Player: " << player << " wins!" << std::endl;
                running = false;
                break;
            }
            else if(checkTie()){
                std::cout << "It's a tie!" << std::endl;
                running = false;
                break;
            }
            player = (player == 'X') ? 'O' : 'X';


        }
        // ending
        std::cout << "Thanks for playing! \n";
        std::cout << "^._.^ ♡♡ \n \n";
    }
};



int main(){
    Game game;
    game.playGame();
    return 0;
}
