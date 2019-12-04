#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <QWidget>
#include <QGraphicsScene>

#include <vector>
#include "tower.hh"

class GameManager
{
public:
    GameManager(int piecesPerTower, int amountOfTowers = 3, QWidget* widget = nullptr);
    ~GameManager();
    void drawTowers(QGraphicsScene* scene); // Draw all towers and pieces on current scene
    bool makeMove(int senderID, int receiverID); // Moves top piece to receiving tower


private:
    std::vector <Tower*> towers;
    int piecesPerTower;
    int amountOfTowers;

    QWidget* parent;
};

#endif // GAMEMANAGER_HH
