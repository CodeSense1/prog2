#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

class Player
{
public:
    Player(std::string name);

    std::string get_name();
    int get_points();
    bool has_won();
    void add_points(int pointsToAdd);

private:
    std::string name;
    int points;

};

#endif // PLAYER_HH
