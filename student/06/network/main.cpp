#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>



const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(! (ignore_empty && new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(! (ignore_empty && tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


bool isNameInConnections(const std::string& name, std::vector<std::string>& connections) {
    for (const auto& connection : connections) {
        if (connection == name)
            return true;
    }

    return  false;
}

std::string s_depth( unsigned int times) {
    std::string space = "";

    for (unsigned int i = 0; i < times; i++)
        space += "..";

    return space;
}

void getUndergroundNetwork(std::vector<std::string>& data,  std::map<std::string, std::vector<std::string>> network, std::vector<int>& depths, int& depth) {

    if (data.size() == 0) {
        depths.push_back(depth);
        depth = 1;
        return;
    } else {

        for (auto& name : data) {
            if (network.find(name) != network.end()) {
                depth++;
                getUndergroundNetwork( network.at(name), network, depths, depth );
            }

        }
    }

    depths.push_back(depth);
    depth = 1;
}

void getConnections(std::vector<std::string>& data, std::map<std::string, std::vector<std::string>> network, int& depth) {


    if (data.size() == 0) {
        return;
    } else {

        for (auto& name : data) {
            if (network.find(name) != network.end()) {
                depth++;
                getConnections( network.at(name), network, depth );
            } else {
                depth++;
            }

        }
    }
}

void printNetwork( std::vector<std::string>& data, std::map<std::string, std::vector<std::string>> network, unsigned int depth) {


    if (data.size() == 0) {
        return;
    } else {

        for (auto& name : data) {
            std:: cout << s_depth(depth);
            if (network.find(name) != network.end()) {
                std::cout << name << std::endl;
                printNetwork( network.at(name), network, depth + 1);
            } else {
                std::cout << name << std::endl;
            }

        }
    }
}

int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string, std::vector<std::string>> network;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        // Saving new connection
        if(command == "S" || command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            // std::map<std::string, std::vector<std::string>>::iterator itr;

            if (network.find(id1) == network.end()) {
                // No connection yet
                std::vector<std::string> id1Connections = {id2};

                network.insert(std::pair<std::string, std::vector<std::string>>(id1, id1Connections));
            } else {

                network.at(id1).push_back(id2);
            }

        // Printing connection
        } else if(command == "P" || command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);
            std::cout << id << std::endl;
            if (network.find(id) == network.end())
                continue;

            printNetwork(network.at(id), network, 1);

        // Printing amount of connections and underground connections
        } else if(command == "C" || command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);
            if (network.find(id) != network.end()) {
                int max = 0;
                getConnections(network.at(id), network, max);
                std::cout << max << std::endl;
            }
            else
                std::cout << 0 << std::endl;


        // Print depth of connections
        } else if(command == "D" || command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            if (network.find(id) == network.end()) {
                std::cout << 1 << std::endl;
            } else {
                int depth = 1;
                std::vector<int> depths = {};

                getUndergroundNetwork(network.at(id), network, depths, depth);

                int max = depths.front();
                for (auto& i : depths) {
                    max = (max < i) ? i : max;
                }

                // I have no idea why there is +1
                std::cout << max +1<< std::endl;

            }


        } else if(command == "Q" || command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
