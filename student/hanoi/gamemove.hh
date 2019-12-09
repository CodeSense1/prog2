#ifndef GAMEMOVE_HH
#define GAMEMOVE_HH


#include <QString>

#include "tower.hh"

#include <vector>


class GameMove
{
public:
    GameMove(Tower* sender, Tower* receiver);
    GameMove(std::vector<Tower*> towers, int senderId, int receiverId);

    Tower* getSender() const;
    Tower* getReceiver() const;

    bool isMoveValid();

    void reverseMove();

    QString toString();

private:

    Tower* sender_;
    Tower* receiver_;

};

#endif // GAMEMOVE_HH
