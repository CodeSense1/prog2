#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}


void readFile( std::string filename, std::map<std::string, std::vector<std::string>> data ) {

}

// Short and sweet main.
int main()
{
    print_rasse();
    return EXIT_SUCCESS;
}
