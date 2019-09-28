/*  Source file for NumberTile class.
 *
 * Also contains an operator for pair addition.
 *
 * Method implementations should be added to the same level as the existing
 * ones.
 * */
#include "numbertile.hh"
#include <iomanip>
#include <iostream>

// Pair addition operator. Allows to do result_pair = pair_1 + pair_2
std::pair<int, int>operator +(std::pair<int, int> lhs, std::pair<int, int> rhs){
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}



// Modify the second line if you don't wish to use pairs.
NumberTile::NumberTile(int value,
                       int x,
                       int y,
                       std::vector<std::vector<NumberTile> > *board)
    : value_(value), x_(x), y_(y), parent_(board)
{
    // Students should write their own implementation here, if necessary.
}

// Enable logging to console, for debugging
std::ostream& operator << (std::ostream& out, NumberTile& tile) {
    return out << "value: " <<  tile.getValue();
}

// Students should not touch this method.
void NumberTile::print(int width)
{
    // std::setw() sets the width of next printable to given amount, usually
    // by adding spaces in front.
    std::cout << "|" << std::setw(width - 1) << value_;
}

int NumberTile::getValue() {
    return this->value_;
}


bool NumberTile::setValue(int value, bool isInitializing)
{

    if (value < 0 || value % 2 != 0)
        return false;

    if (value_ == 0) {

        value_ = value;
        return true;
    } else if (!isInitializing) {
        value_ = value;
    }

    return false;

}

