#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(std::vector<int> ints) {

    int first = ints[0];

    for (const auto& i : ints) {
        if (first != i) {
            return false;
        }
    }
    return true;
}

bool is_ordered_non_strict_ascending(std::vector<int> ints) {
    int last = ints[0];
    for (const auto& i : ints) {
        if (i >= last) { // kelpaa, koska identtiset arvot sallitaan
            last = i;
        } else {
            return false;
        }
    }

    return true;
}

bool is_arithmetic_series(std::vector<int> ints) {
    // Oletetaan, että 'ints' sisältää yli 2 alkiota
    int first = ints[0];
    int last = ints[1];
    int diff = last - first;

    for (unsigned int i = 1; i < ints.size(); i++) {
        last = ints[i];
        first = ints[i-1];
        if (last - first == diff) {
            diff = last-first;
        } else {
            return false;
        }
    }

    return true;
}

bool is_geometric_series(std::vector<int> ints) {
    int first = ints[0];
    int last = ints[1];
    double diff = static_cast<double>(first)/static_cast<double>(last);

    for (unsigned int i = 1; i < ints.size(); i++) {
        first = ints[i-1];
        last = ints[i];

        if (static_cast<double>(first)/static_cast<double>(last) == diff) {

            diff = static_cast<double>(first)/static_cast<double>(last);
        } else {
            return false;
        }
    }

    return true;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
