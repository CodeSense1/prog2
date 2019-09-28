/* Numbers ( or 2048, but that's an invalid name ) : Template code
 *
 * Desc:
 *  This program generates a game of 2048, a tile combining game
 * where the goal is to get from 2's to 2048. The board is SIZE x SIZE,
 * ( original was 4x4 ) and every round the player chooses a direction
 * to which the tiles should fall. If they collide with a wall or a different
 * value, they will move as close as they can get. If they collide with
 * a tile with same value, they will combine and double the value. The
 * tile will continue to move until a wall or other tile comes along, but a
 * single tile can only be combined once per "turn".
 *  Game will end when the goal value asked (orig 2048) is reached or new
 * tile can't be added to the board.
 *
 * Program author
 * Name: Joonas Kakkuri
 * Student number: 274166
 * UserID: kakkuri
 * E-Mail: joonas.kakkuri@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * I think NumberTile class is completely useless in my implementation. Simple
 * int would have been enough in my case. Even though it adds complexity and
 * extra confusion I decided to keep it as a part of the program.
 * I thought that removing it would result in lost point since
 * authors, who made this example decided to implement it.
 *
 * */

#include "numbertile.hh"
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <ctime>

const int SIZE = 4;
const int NEW_VALUE = 2;
const int PRINT_WIDTH = 5;
const int DEFAULT_GOAL = 2048;

// Since we are using this data type quite a lot, let's simplify it
using Board = std::vector<std::vector<NumberTile>>;

// enum for different directions where tiles can move
enum DIR {W, A, S, D, NONE};


// Adds a single new value to board using rEng and distr for random positioning.
void newValue(Board* board,
              std::default_random_engine &rEng,
              std::uniform_int_distribution<int> &distr){


    // Tries to assign NEW_VAl to randomly selected tile. Continues trying until
    // newVal() returns true.
    while(!board->at(distr(rEng)).at(distr(rEng)).setValue(NEW_VALUE, true));
}

// Initializes the board to size SIZE x SIZE and adds SIZE tiles with NEW_VALUE
// to it through new_value() func after initializing the random engine with
// a seed value.
void initBoard(Board &board,
               std::default_random_engine &rEng,
               std::uniform_int_distribution<int> &distr) {


    // Initialize the board with SIZE x SIZE empty numbertiles.
    for ( auto y = 0; y < SIZE; y++ ){
        board.push_back({});
        for ( auto x = 0; x < SIZE; x++ ){
            // If you don't want to use pairs, replace "std::make_pair(y, x)"
            // with "y, x".

            board.at(y).push_back(NumberTile(0, x, y, &board));
        }

    }

    // Ask user for the seed value and initialize rEng.
    std::cout << "Give a seed value or an empty line: ";
    std::string seed = "";
    getline(std::cin, seed);


    if(seed == "") {
        // If the user did not give a seed value, use computer time as the seed
        // value.
        rEng.seed(time(NULL));
    } else {
        // If the user gave a seed value, use it.
        rEng.seed(stoi(seed));
    }

    // Add some tiles to the board.
    for ( int i = 0 ; i < SIZE ; i++ ){
        newValue(&board, rEng, distr);
    }
}

// Prints the board.
void print(Board &board){
    // The y isn't actually the y coordinate or some int, but an iterator that
    // is like a vector of NumberTiles.
    for ( auto y : board ){
        // Prints a row of dashes.
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        // And then print all cells in the desired width.
        for ( auto x : y ){
            x.print(PRINT_WIDTH);
        }
        // And a line after each row.
        std::cout << "|" << std::endl;
    }
    // Print a last row of dashes so that the board looks complete.
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}


void slide( std::vector<NumberTile>& arr ) {
    /*  Slides one row. It does not combine, so you might have
     *  situation where 2 0 2 0 results 2 2 0 0
     *  Values greater than zero will be moved towards the beginning of the
     *  vector.
     *
     *  param: arr - type: vector<NumberTile>, represents one column
     *               on the board
     *
     *  return: void
     */

    std::vector<int> values = {};


    for (auto i : arr)
        values.push_back(i.getValue());

    auto copy = values;
    int index = 0;
    for (int k = 0; k < SIZE-1; k++) {

        if (values.at(index) == 0) {
            // shift values (if > 0) towards the beginning of the vector
            copy = values;
            for (int i = index; i < SIZE; i++) {
                if (i + 1 == SIZE)
                    values.at(i) = copy.at(index);
                else
                    values.at(i) = copy.at(i+1);
            }

        } else
            index++;
    }

    for ( int v = 0; v < SIZE; v++) {
        arr.at(v).setValue(values.at(v));
    }
}

void combine( std::vector<NumberTile>& arr ) {
    /*  Combines two subsequent tiles. Combined tile will be towards
     *  the beginning of the vector. Other tile will be reset to 0.
     *  Modifies given vector accordingly.
     *
     *  param: arr - type: vector<NumberTile>, represents one column
     *               on the board
     *
     *  return: void
     */

    for ( int i = 0; i < arr.size()-1; i++ ) {
        if (arr.at(i).getValue() == arr.at(i+1).getValue()
                && arr.at(i).getValue() != 0) {

            arr.at(i).setValue(arr.at(i).getValue() + arr.at(i+1).getValue());
            arr.at(i+1).setValue(0);
        }
    }
}

bool hasWon(Board board, const int optionalScore) {

    /*
     * Returns true if player has reached defaul goal (2048) or
     * optinal goal.
     *
     * param:   board - current game board
     *          optionalScore - Game winning score
     *
     * return:  bool - has player won the game
     *
     */

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (board.at(j).at(i).getValue() >= optionalScore ||
                    board.at(j).at(i).getValue() >= DEFAULT_GOAL) {
                return true;
            }
        }
    return false;
}

bool gameOver(Board board) {
    /*
     * Checks every tile and it's neighbours. If two neighbours have same value
     * game is not over yet
     *
     */

    for (int x = 0; x < SIZE; x++)
        for (int y = 0; y < SIZE; y++) {
            NumberTile cur = board.at(y).at(x);

            if (cur.getValue() == 0)
                return false;

            // Check tiles around current tile
            for (int i = -1; i < 2; i++)
                for (int j = -1; j < 2; j++) {
                    if(x+i > 0 && x+i < SIZE-1 && y+j > 0 && y+j < SIZE-1) {
                        // There are two tiles with same number, player can make move
                        if( board.at(y+j).at(x).getValue() == cur.getValue() ||
                            board.at(y).at(x+i).getValue() == cur.getValue())
                            return false;
                    }
                }
        }

    return true;

}

bool hasEmptySpaces(Board board) {

    // check if board has space for new value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board.at(j).at(i).getValue() == 0)
                return true;
        }
    }
    return false;
}


void update(Board& board, DIR d) {
    // Makes a move on the board and updates all events on the board

    // param: board - reference to current game board
    //        d     - direction, where board should be moved


    // return: void

    if (d == W) {
        for (int x = 0; x < SIZE; x++) {

            // Construct column
            std::vector<NumberTile> col = {};
            for (int y = 0; y < SIZE; y++) {
                col.push_back(board.at(y).at(x));
            }

            // Slide values upwards
            slide(col);
            combine(col);
            slide(col);
            for (int i = 0; i < SIZE; i++)
                board.at(i).at(x) = col.at(i);
        }
    }

    if (d == A) {
        for (int y = 0; y < SIZE; y++) {

            // Construct row
            std::vector<NumberTile> row = {};
            for (int x = 0; x < SIZE; x++) {
                row.push_back(board.at(y).at(x));
            }

            // Slide values to the left
            slide(row);
            combine(row);
            slide(row);
            for (int i = 0; i < SIZE; i++)
                board.at(y).at(i) = row.at(i);

        }
    }

    if (d == S) {
        for (int x = 0; x < SIZE; x++) {

            // Construct column
            std::vector<NumberTile> col = {};
            for( int y = SIZE-1; y > -1; y--) {
                col.push_back(board.at(y).at(x));
            }
            // Slide values down
            slide(col);
            combine(col);
            slide(col);
            for (int i = 0; i < SIZE; i++)
                board.at(i).at(x) = col.at(SIZE-1-i);
        }
    }

    if (d == D) {
        for (int y = 0; y < SIZE; y++) {

            // Construct row
            std::vector<NumberTile> row = {};
            for (int x = SIZE-1; x > -1; x--)
                row.push_back(board.at(y).at(x));

            // Slide values to the right
            slide(row);
            combine(row);
            slide(row);
            for (int i = 0; i < SIZE; i++)
                board.at(y).at(i) = row.at(SIZE-1-i);

        }
    }

}

int main() {
    // SETUP //

    // Declare the board and randomengine.
    Board board;
    std::default_random_engine randomEng;
    // And initialize the disrt to give numbers from the correct
    std::uniform_int_distribution<int> distr(0, SIZE - 1);

    initBoard(board, randomEng, distr); // initialize board

    // Define optional goal before printing the board
    std::string input;
    std::cout << "Give a goal value or and empty line: ";
    getline(std::cin, input);

    const int OPTIONAL_GOAL = (input != "") ? std::stoi(input) : DEFAULT_GOAL;

    print(board);

    bool running = true;

    // UPDATE
    while (running) {
        std::cout << "Dir> ";
        char dir;
        std::cin >> dir;

        DIR direction;

        // Respond accordingly
        switch (dir) {

            case 'w': { direction = W; break;      }
            case 'a': { direction = A; break;      }
            case 's': { direction = S; break;      }
            case 'd': { direction = D; break;      }
            case 'q': { running = false; continue; }

            default: {
                std::cout <<
                             "Error: unknown command."
                          << std::endl;
                direction = NONE;
                break;
            }

        }

        update(board, direction);
        if (!hasEmptySpaces(board)) {
            std::cout << "Can't add new tile, you lost!" << std::endl;
            running = false;
            continue;
        }

        newValue(&board, randomEng, distr);
        print(board);

        if (hasWon(board, OPTIONAL_GOAL)) {
            std::cout << "You reached the goal value of " << OPTIONAL_GOAL << "!" << std::endl;
            running = false;
        } else if (hasWon(board, DEFAULT_GOAL)) {
            std::cout << "You reached the goal value of 2048!" << std::endl;
            running = false;
        }

        if (gameOver(board)) {
            std::cout << "Can't add new tile, you lost!" << std::endl;
            running = false;
        }
    }
}
