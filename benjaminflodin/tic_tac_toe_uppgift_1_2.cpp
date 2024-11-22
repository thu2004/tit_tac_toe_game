#include <iostream>
#include <cstdlib>
#include <limits>
#include <random>
#include <map>
#include <set>
#include <string>

void clear_screen() {
    std::cout << "\033[2J\033[H";
}

int number_input_check()
{
    int temp_num;
    while(1)
    {
        std::cin >> temp_num;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input!\n";
        }
        else if(temp_num >= 1 && temp_num <= 9)
            break;
        else
            std::cout << "Out of range!\n";
    }
    return temp_num;
}

int pc_num_horizontal_pick()
{
    int temp_num;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> range(1,9);
    temp_num = range(gen);
    
    return temp_num;
}

int who_starts_random()
{
    int temp_num;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> range(0,1);
    temp_num = range(gen);
    
    return temp_num;
}

int pc_num_vertical_pick()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);

    
    int choices[] = {1, 3, 5};

    
    int temp_num = choices[dist(gen)];

    return temp_num;

}

void clear_input_buffer() {
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}




class Board
{
    public:

        Board() {}
    
        char game_board[6][5] =
        {   '1','|','2','|','3',
            '-','|','-','|','-',
            '4','|','5','|','6',
            '-','|','-','|','-',
            '7','|','8','|','9',
            '-','|','-','|','-'
        };
        static void print_game_board(char game[6][5])
        {
            for(int i = 0; i < 6; ++i)
            {
                for(int j = 0; j < 5; ++j)
                {
                    std::cout << game[i][j] << ' ';
                }
                std::cout << std::endl;
            } 
        }

        static void reset_gameboard(char game[6][5])
            {
                // index 0 2 4
                // rader 1 3 5
                game[1][0] = '-';
                game[1][2] = '-';
                game[1][4] = '-';
                game[3][0] = '-';
                game[3][2] = '-';
                game[3][4] = '-';
                game[5][0] = '-';
                game[5][2] = '-';
                game[5][4] = '-';
            }

};

class TicTacToe : public Board
{
    
    public:
        
        static int pvp_player_1_score;//player 1 score 
        static int pvp_player_2_score;//player 2 score
        static int pvc_player_1_score; //score vs pc
        static int pvc_computer_score; //pc score

        static void show_statistics()
        {    
            std::cout << "----STATISTICS----\n";
            std::cout << "Player 1 wins (PVP): " << pvp_player_1_score << "\n";
            std::cout << "Player 2 wins (PVP): " << pvp_player_2_score << "\n";
            std::cout << "------------------\n";
            std::cout << "Player wins (PVC): " << pvc_player_1_score << "\n";
            std::cout << "Computer wins (PVC): " << pvc_computer_score << "\n";
                
            std::cout << "\nPress ENTER to return to main menu...\n"; 
            clear_input_buffer();
            std::cin.get();
        }
        

        static bool check_win(char game[6][5], char player_sign)
            {
                // index 0 2 4
                // rader 1 3 5
                
                if(game[1][0] == player_sign && game[1][2] == player_sign && game[1][4] == player_sign ||
                    game[3][0] == player_sign && game[3][2] == player_sign && game[3][4] == player_sign ||
                    game[5][0] == player_sign && game[5][2] == player_sign && game[5][4] == player_sign)
                    return true;
                
                else if(game[1][0] == player_sign && game[3][0] == player_sign && game[5][0] == player_sign ||
                        game[1][2] == player_sign && game[3][2] == player_sign && game[5][2] == player_sign ||
                        game[1][4] == player_sign && game[3][4] == player_sign && game[5][4] == player_sign)
                        return true;
                
                else if(game[1][0] == player_sign && game[3][2] == player_sign && game[5][4] == player_sign ||
                        game[1][4] == player_sign && game[3][2] == player_sign && game[5][0] == player_sign)
                        return true;
                else
                    return false;           
            }
        
        static bool is_draw(char game[6][5])
        {
                    
            for (int i = 1; i <= 5; i += 2) 
            {
                for (int j = 0; j <= 4; j += 2) 
                {
                    if (game[i][j] == '-') 
                    {
                        return false; // tomma platser kvar
                    }
                }
            }
            return true; // game draw
        }
        

        static void player_vs_player_game(char game[6][5]) {
            bool player1 = true; // true == player1, false == player2
            std::set<int> used_numbers; 

            while (1) {
                clear_screen();
                if(player1)
                    std::cout << "Player 1 turn:\n";
                else
                    std::cout << "Player 2 turn:\n";
                
                std::cout<<std::endl;

                print_game_board(game);
                
                int player_pick;
                
                
                while (1) {
                    
                    player_pick = number_input_check();
                    
                    
                    if (used_numbers.find(player_pick) == used_numbers.end()) {
                        used_numbers.insert(player_pick); 
                        break; 
                    } else {
                        std::cout << "That spot is already taken!\n";
                    }
                }

                // Place the player's symbol on the board
                char player_symbol = (player1) ? 'x' : 'o';
                place_move_on_board(game, player_pick, player_symbol);
                
                // Check if the game is over
                if (check_win(game, 'x') || check_win(game, 'o')) {
                    clear_screen();
                    print_game_board(game);
                    if (check_win(game, 'x'))
                    {
                        std::cout << "Player 1 (x) won the game!\n";
                        pvp_player_1_score++;
                        std::cout << "Press ENTER to return to main menu...\n"; 
                        clear_input_buffer();
                        std::cin.get();
                    }
                    else if (check_win(game, 'o'))
                    {
                        std::cout << "Player 2 (o) won the game!\n";
                        pvp_player_2_score++;
                        std::cout << "Press ENTER to return to main menu...\n"; 
                        clear_input_buffer();
                        std::cin.get();
                    }
                    reset_gameboard(game); 
                    break; 
                }
                else if (is_draw(game))
                {
                    std::cout << "It's a draw!\n";
                    std::cout << "Press ENTER to return to main menu...\n"; 
                    clear_input_buffer();
                    std::cin.get();
                    reset_gameboard(game);
                    break;
                }

                
                player1 = !player1; //byte av spelare
            }
        }

        // Helper function to place the player's move on the board
        static void place_move_on_board(char game[6][5], int position, char player_symbol) {
            // Map positions to the coordinates on the board
            int row = (position - 1) / 3 * 2 + 1;  // Calculates which row (1, 3, 5)
            int col = (position - 1) % 3 * 2;      // Calculates which column (0, 2, 4)

            game[row][col] = player_symbol; // Place the player's symbol
        }
                    

};










int TicTacToe::pvp_player_1_score = 0;
int TicTacToe::pvp_player_2_score = 0;
int TicTacToe::pvc_player_1_score = 0;
int TicTacToe::pvc_computer_score = 0;

int main(int argc, char const *argv[])
{

    while (1)
    {    
        clear_screen();
        std::cout << "|-----MAIN_MENU-----|\n";
        std::cout << "|----NEW_GAME(1)----|\n";
        std::cout << "|---STATISTICS(2)---|\n";
        std::cout << "|------QUIT(3)------|\n";
        
        char menu_answ;
        std::cin >> menu_answ;
        clear_input_buffer();
        
        Board* board = new Board;

        switch (menu_answ)
        {
        case '1':
            clear_screen();
            std::cout << "------NEW_GAME------\n";
            std::cout << "Player vs Player (1)\n";
            std::cout << "Player vs Computer (2)\n";
            std::cout << "Return to main menu (3)\n";
            
            std::cin >> menu_answ;
            clear_input_buffer();
            switch (menu_answ)
            {
            case '1':
                TicTacToe::player_vs_player_game(board->game_board);
                delete board;
                board = nullptr;
                break;
            case '2':
                clear_screen();
                std::cout << "This content does not exist yet!\n";
                std::cout << "Press ENTER to return to main menu...\n"; 
                clear_input_buffer();
                std::cin.get();
                break;
            case '3':
                std::cin.clear();
                std::cin.ignore();
                break;
            default:
                break;
            }
            break;
        case '2':
            clear_screen();
            TicTacToe::show_statistics();
            break;
        case '3':
            std::cout << "Thank you for playing!\n";
            exit(0);
            break;
        default:
            std::cout << "Try again!\n";
        }

    }

    return 0;
}
