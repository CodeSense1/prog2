#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


struct Data {

    std::string name;
    int points;
    Data ( std::string name_, int points_) {

        name = name_;
        points = points_;
    }

};

void findAndAdd(std::vector<Data>& data, const std::string& name, const int& points) {

    for (auto& i : data) {
        if (i.name == name) {
            i.points = i.points + points;
            return;
        }
    }
    data.push_back( Data(name, points) );
}

bool sort(const Data& f, const Data& s) {
    return (f.name < s.name);
}



std::vector<Data> readFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        return {};
    }

    std::vector< Data > data = {};
    std::string line;
    while( getline(file, line) ) {
        size_t index = line.find(':');
        std::string name = line.substr(0,index);
        int points = std::stoi(line.substr(index+1, line.length()));
        findAndAdd(data, name, points);
    }

    // sort data
    std::sort(data.begin(), data.end(), sort);

    return data;
}


int main()
{
    std::string file;
    std::cout << "Input file: ";
    getline(std::cin, file);

    auto data = readFile(file);


    if (data.size() == 0) {
        std::cout << "Error! The file " << file << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }


    std::cout << "Final scores: " << std::endl;
    for (const auto& i : data) {
        std::cout << i.name << ": " << i.points << std::endl;
    }

    return 0;
}
