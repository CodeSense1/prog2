#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string line, char sep, bool passEmpty = false) {
    std::vector<std::string> result = {};

    std::string tmp;
    for (auto c : line) {

        if (c == sep) {
            if (passEmpty && tmp.length() < 1) {
                tmp = "";
                continue;
            }
            result.push_back(tmp);
            tmp = "";
        }
        else {
            tmp += c;
        }
    }

    // Add last element
    if (passEmpty && tmp.length() < 1) {
        return result;
    }
    result.push_back(tmp);

    return result;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
