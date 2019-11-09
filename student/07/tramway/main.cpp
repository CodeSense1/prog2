
/*
 * Author: Joonas Kakkuri
 * email: joonas.kakkuri@tuni.fi
 * student ID: 274166
 *
 *
 * Project Rasse:
 *
 * Mahtava sovellus, joka kuvastaa RASSEN matkailua pitkin Tamperetta
 * Sovelluksella voi tarkastella, lisätä sekä poistaa
 * pysäkkejä sekä reittäjä RASSEN matkan varrella
 *
 *
 *
 * Viimeksi tuli palautetta kommenttien vähyydestä, joten
 * nyt niitä sitten on. (n. 200 riviä) :)
 *
 * Joku kertoi joskus, että funktion parametrit on parempi
 * laittaa vakio viitteenä funktioon, sillä säästyy turhalta muuttujien kopioinnilta.
 * Kertokaa toki jos tässä niitä on käytetty väärin.
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>

#include <vector>
#include <map>
#include <set>


using TramlineMap = std::map<std::string, std::vector<std::string>>;

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

/////////////////////////////////////////////////////////////////////////////////
///////////////////////// GENERAL HELP FUNCTION /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void printErrorMsg() {
    std::cout << "Error: Invalid input." << std::endl;
}

bool split( std::string command,
            const char& delimiter,
            std::vector<std::string> &args) {

    /* Splits line on delimiter. Delimiters between quotes
     * are ignored
     *
     * param:
     *  command: Type std::string
     *           Input command that is splitted into arguments
     *
     *  delimiter: Type char
     *             Character that indicates where to split the string
     *
     *  args: Type vector<string>
     *        Vector where arguments will be stored
     *
     * return: boolean
     *         true if reading the file was succesful
     */

    if (command.length() == 0) {
        return true;
    }

    std::string line;
    if (command.front() == '"') {
        // Deal with quotes
        command = command.substr(1, command.size()-1);
        size_t anotherQuote = command.find('"');

        if (anotherQuote == std::string::npos) {
            // No matching quote found
            return false;
        }

        line = command.substr(0, anotherQuote);
        if (line.length() == 0)
            return false;


        args.push_back(line);
        split(command.substr(anotherQuote+1, command.size()-1), delimiter, args);

    } else {

        // Search for delimiter
        size_t index = command.find(delimiter);

        if (index == std::string::npos) {
            // No more delimiters
            args.push_back(command);
            return (args.size() != 1);
        }

        // Delimiter found
        line = command.substr(0, index);

        if (line.length() == 0)
            return false;

        args.push_back(line);

        // Split all that is left
        split(command.substr(index+1, command.size()-1), delimiter, args);
    }

    return (args.size() != 1);


}

bool readFile( const std::string &filename, TramlineMap &data ) {

    /* Reads file from the directory and
     * occupies given datastucture.
     *
     * param:
     *  filename: Type std::string
     *            filename containing information about tramlines
     *
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     *
     * return: boolean
     *         true if reading the file was succesful
     */


    std::ifstream inputFile(filename); // File object
    std::string line;

    if (!inputFile.is_open()) {
        std::cout << "Error: File could not be read." << std::endl;
        return false;
    }

    // Iterate through files lines
    while(getline(inputFile, line)) {

        std::vector<std::string> args = {};

        // Split line at ';' and add tramlines
        if (split(line, ';', args)) {

            line = args.at(0);
            std::string station = args.at(1);
            if (data.find(line) != data.end()) {

                // There is line already in tramlines
                // Check if given station is already added
                for ( std::string stop : data.at(line)) {

                    if (stop == station) {
                        // Prevent adding line twice
                        std::cout << "Error: Station/line already exists." << std::endl;
                        return false;
                    }
                }
                // Add new stop in direction
                data.at(line).push_back(station);
            } else {
                // Line is not found in datastructure, let's add new line and station
                // Add new direction and stop
                data.insert({ line, std::vector<std::string>({station}) } );
            }
        } else {
            std::cout << "Error: Invalid format in file." << std::endl;
            return false;
        }
    }

    return true;
}

bool lineExists(const TramlineMap& data, const std::string& line) {

    /* Does line exist in tramlines
     *
     * param:
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     *
     *  line: Type std::string
     *        Name of the line we are checking
     *
     *
     * return: boolean
     *         true if instance of line is found
     */
    return data.find(line) != data.end();
}

bool stationExistsInLine(const TramlineMap& data,
                         const std::string& line,
                         const std::string& station) {

    /* checks if station is already in line
     * Use this when adding new lines
     *
     * param:
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     *
     *  line: Type std::string
     *        Name of the line we are checking
     *
     *  station: Type std::string
     *           Name of the station we are checking
     *
     * return: boolean
     *         true if instance on station is found
     *         from line
     */


    if (lineExists(data, line)) {
        // Given line was found

        for (std::string stop : data.at(line)) {
            // Check if given station already exists
            if (stop == station) {
                // std::cout << "Error: Station/line already exists." << std::endl;
                return true;
            }
        }

    } else {
        // Line is not found
        // std::cout << "Error: Line could not be found." << std::endl;
        return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////  COMMAND HANDLING FUNCTIONS ///////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void printTramLines(TramlineMap& tramLineData) {

    /* Prints all tramlines and stations
     *
     * param:
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     *
     * return: void
     */


    TramlineMap::iterator it;
    for (it = tramLineData.begin(); it != tramLineData.end(); it++) {
        for (std::string station : it->second) {

            std::cout << it->first << ": " << station << std::endl;
        }
    }
}

void printLines( TramlineMap& data) {

    /* Prints all tramlines in alphabetical order
     *
     * param:
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     *
     * return: void
     */

    std::cout << "All tramlines in alphabetical order: " << std::endl;
    TramlineMap::iterator line;
    for ( line = data.begin(); line != data.end(); line++ ) {
        std::cout << line->first << std::endl;
    }
}

void printStations( TramlineMap& data) {

    /*
     * Prints all stations in alphabetical order
     *
     * param:
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     *
     * return: void
     */

    // Set for storing unique stations to avoid duplicates
    std::set<std::string> stations;
    TramlineMap::iterator it;

    // Loop through all elements in data structure
    for (it = data.begin(); it != data.end(); it++) {
        for (std::string station : it->second) {

            // Add all stations from each line
            stations.insert(station);
        }
    }

    if (stations.size() > 0 ) {
        // Print all found stations
        std::cout << "All stations in alphabetical order: " << std::endl;
        for (std::string station : stations) {
            std::cout << station << std::endl;
        }
    }
}

void addline(const std::vector<std::string>& args, TramlineMap& data) {
    /*
     * Adds new line to Tramline map
     *
     * param:
     *  args: Type vector<string>
     *        0: Command (ADDSTATION)
     *        1: line name
     *
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     *
     * return: void
     */


    // Add new line

    // In the future if we want to add
    // multiple lines simultaneously, modify this
    if (args.size() != 2) {
        printErrorMsg();
        return;

    }

    std::string line = args.at(1);

    if ( !lineExists(data, line) ) {

        // No instance of line found
        // Add new line with no stations
        data.insert({line, std::vector<std::string>()} );
        std::cout << "Line was added." << std::endl;

    } else {
        std::cout << "Error: Station/line already exists." << std::endl;
    }
}

void addStation(const std::vector<std::string>& args, TramlineMap& data) {

    /*
     * Adds new station to tramlines
     * By spesifying next station, new station will be inserted
     * before next station.
     *
     *
     * param:
     *  args: Type vector<string>
     *        0: Command (ADDSTATION)
     *        1: line name
     *        2: new station name
     *        3: (optional) next station
     *
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     */

    // Add new stations to line
<<<<<<< HEAD
    return false;
=======
    // Add station to existing line
    if (args.size() < 3) {

        // 3 arguments are mandatory
        printErrorMsg();
        return;
    }

    std::string line = args.at(1);
    std::string station = args.at(2);

    std::string nextStation = (args.size() > 3) ? args.at(3) : "";

    if (!stationExistsInLine(data, line, station)) {
        // Given line was found and station is not part of that line
        // Let's add new station(s)

        // Check if next station exists in line
        if (stationExistsInLine(data, line, nextStation)) {

            // Find position of next station
             std::vector<std::string>::iterator it = std::find(data.at(line).begin(),
                                                               data.at(line).end(),
                                                               nextStation);

             // Insert new station to correct place
             data.at(line).insert(it, station);
        } else {
            data.at(line).push_back(station);
        }
        std::cout << "Station was added." << std::endl;

    } else {
        std::cout << "Error: Station/line already exists." << std::endl;
    }


}

void removeStation(const std::vector<std::string>& args, TramlineMap& data) {
    /*
     * Removes station in Tramline map
     *
     * param:
     *  args: Type vector<string>
     *        0: Command (REMOVE)
     *        1: station name
     *
     *  data: Type TramlineMap, map<string, vector<string>>
     *        Datastructure used for storing information
     *        about tramlines and stations.
     *
     * return: void
     */

    if (args.size() != 2) {
        printErrorMsg();
        return;
    }

    TramlineMap::iterator it;

    std::string station = args.at(1);
    bool instanceFound = false;

    for (it = data.begin(); it != data.end(); it++ ) {
        // Search station from each line
        if (stationExistsInLine(data, it->first, station)) {
            instanceFound = true;
            // Station was found, let's delete it
            std::vector<std::string>::iterator stationToErase;
            stationToErase = std::find(it->second.begin(), it->second.end(), station);

            it->second.erase(stationToErase);
        }
    }

    if (instanceFound) {
        std::cout << "Station was removed from all lines." << std::endl;
    } else
        std::cout << "Error: Station could not be found." << std::endl;
}


void printStationsInLine(const std::vector<std::string>& args, const TramlineMap& data) {
    /*
     * Prints all stops at given line
     *
     * param:
     *  args:   Type vector<string>. Holds data of arguments
     *          0: command (LINE)
     *          1: name of the line
     *
     *  data:   Type TramlineMap, map<string, vector<string>>
     *          Datastructure used for storing information
     *          about tramlines and stations.
     *
     *
     *  return: void
     *
     */


    // Prints all stations in specified line
    if (args.size() != 2) {
        // Too many or too few arguments
        printErrorMsg();
        return;
    }

    // Print line with given argument
    std::string line = args.at(1);

    // Check if given line exists in all active lines
    if (lineExists(data, line)) {

        std::cout << "Line "
                  << line
                  << " goes through these stations in the order they are listed:"
                  << std::endl;

        // Given line is found in lines
        // Print all stations in that line
        for (std::string station : data.at(line))
            std::cout << " - " << station << std::endl;


    } else {
        // given line is not found
        std::cout << "Error: Line could not be found." << std::endl;
    }
>>>>>>> c41b241ebf44eea12ee8a1315f69309035fdf350
}

void printLinesInStation(const std::vector<std::string>& args, TramlineMap& data) {
    /*
     * Prints all lines that goes through specified station
     *
     * param:
     *  args:   Type vector<string>. Holds data of arguments
     *          0: command (STATION)
     *          1: name of the station
     *
     *  data:   Type TramlineMap, map<string, vector<string>>
     *          Datastructure used for storing information
     *          about tramlines and stations.
     *
     *
     *  return: void
     *
     */

    if (args.size() != 2) {
        printErrorMsg();
        return;
    }

    // Station that we are checking
    std::string station = args.at(1);

    // Placeholder for lines, that drive through given station
    std::set<std::string> lines;


    TramlineMap::iterator it;
    for (it = data.begin(); it != data.end(); it++) {
        // Loop through all stations in every line

        for (std::string stop : it->second) {
            if (stop == station) {
                // Add found station to set of unique stations
                lines.insert(it->first);

                // One station already found in this line,
                // no point checkin for more
                break;
            }
        }
    }

    if (lines.size() > 0) {

        // print lines that drove through given station
        std::cout << "Station "
                  << station
                  << " can be found on the following lines:"
                  << std::endl;

        for (std::string line : lines) {
            std::cout << " - " << line << std::endl;
        }
    } else {

        std::cout << "Error: Station could not be found." << std::endl;
    }
}



// Short and sweet main.
int main()
{

    // Print magnificient Rasse
    print_rasse();

    // Initialize data structure
    std::map<std::string, std::vector<std::string>> tramLineData = {};
    std::string filename;

    std::cout << "Give a name for input file: ";
    getline(std::cin, filename);


    if (!readFile(filename, tramLineData)) {
        return EXIT_FAILURE;
    }


    // Program mainloop
    while (true) {
        std::cout << "tramway> ";
        std::string command;
        getline(std::cin, command);

        std::vector<std::string> args;

        // Get arguments if there are any
        split (command, ' ', args);

        command = args.at(0);

        // Deal with lowercase commands
        std::transform(command.begin(), command.end(),command.begin(), ::toupper);


             if ( command == "QUIT"      )   { return EXIT_SUCCESS;                          }
        else if ( command == "LINES"     )   { printLines(tramLineData);                     }
        else if ( command == "LINE"      )   { printStationsInLine(args, tramLineData);      }
        else if ( command == "STATIONS"  )   { printStations(tramLineData);                  }
        else if ( command == "STATION"   )   { printLinesInStation(args, tramLineData);      }
        else if ( command == "ADDLINE"   )   { addline(args, tramLineData);                  }
        else if ( command == "ADDSTATION")   { addStation(args, tramLineData);               }
        else if ( command == "REMOVE"    )   { removeStation(args, tramLineData);            }
        else                                 { printErrorMsg();                              }


    }

}
