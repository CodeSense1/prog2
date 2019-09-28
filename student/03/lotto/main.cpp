#include <iostream>

unsigned long int factorial(int num)
{
    // calculate factorial of num
    unsigned long int result = static_cast<unsigned long int>(num);

    if (result == 0)
    {
        return 1;
    }

    for (int i = num - 1; i > 0; i--)
    {
        result *= static_cast<unsigned long int>(i);
    }
    return result;
}

unsigned long int ncr(int n, int k)
{

    unsigned long int top = factorial(n);
    unsigned long int bottom = factorial(k) * factorial(n - k);

    // std::cout <<"top: " << top << " bottom: " << bottom << std::endl;

    return static_cast<unsigned long int>(top / bottom);
}

int main()
{

    std::cout << "Enter the total number of lottery balls: ";
    int balls = 0;
    std::cin >> balls;

    std::cout << "Enter the number of drawn balls: ";
    int drawn = 0;
    std::cin >> drawn;

    if (balls < 1)
    {
        std::cout << "The number of balls must be a positive number." << std::endl;
    }
    else if (drawn > balls)
    {
        std::cout << "The maximum number of drawn balls is the total amount of balls." << std::endl;
    }
    else
    {
        std::cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << ncr(balls, drawn) << std::endl;
    }

    std::system("pause");
}
