#include <iostream>

// Write here a function counting the mean value
float avg(int sum, int total) {
    return (float)sum/(float)total;
}

int main()
{
    std::cout << "From how many integer numbers you want to count the mean value? ";
    int total;
    std::cin >> total;

    if (total < 1) {
        std::cout << "Cannot count mean value from " << total << " numbers" << std::endl;
        return 0;
    }

    int sum = 0;

    for(int i = 1; i < total+1; i++) {
        std::cout << "Input " << i <<". number: ";
        int num;
        std::cin >> num;

        sum += num;

    }

    std::cout << "Mean value of the given numbers is " << avg(sum, total) << std::endl;
}
