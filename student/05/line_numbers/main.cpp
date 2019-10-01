#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main()
{
    // "D:/koodausta/kakkuri/student/05/line_numbers/" +

    std::string fileName = "";
    std::cout << "Input file: ";
    getline(std::cin, fileName);

    std::string outputFileName = "";
    std::cout << "Output file: ";
    getline(std::cin, outputFileName);

    std::ifstream file(fileName);
    std::vector<std::string> output = {};
    std::string line;
    int lineNumber = 1;

    if (!file) {
        std::cout << "Error! The file " << fileName << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    while ( getline(file, line) ) {

        output.push_back(std::to_string(lineNumber) + " " + line);
        lineNumber++;
    }

    file.close();

    std::ofstream outputFile(outputFileName);

    for (auto l : output) {
        outputFile << l << std::endl;
    }

    outputFile.close();

    return 0;
}
