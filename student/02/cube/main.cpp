#include <iostream>
#include <cmath>

int cube(int num) {

    return pow(num, 3);
}

int main()
{
    std::cout << "Enter a number: ";
    int num;
    std::cin >> num;

    int result = cube(num);

    if (num > 0 && result < 0) {
        std::cout << "Error! The cube of " << num << " is not " << result<< "."<< std::endl;
    } else if (num > result) {
        std::cout << "Error! The cube of " << num << " is not " << result<< "."<< std::endl;
    } else {
        std::cout << "The cube of " << num << " is " << result << "." << std::endl;

    }
    return 0;
}
