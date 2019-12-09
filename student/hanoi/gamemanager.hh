#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include "ui_mainwindow.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QSizeF>

#include <vector>

#include "tower.hh"
#include "gamemove.hh"


class GameManager
{
public:
    GameManager(int piecesPerTower, int amountOfTowers = 3, QWidget* widget = nullptr);
    ~GameManager();
    void setUi(Ui::MainWindow* ui);


    void drawTowers(QGraphicsScene* scene); // Draw all towers and pieces on current scene
    bool makeMove(int senderID, int receiverID); // Moves top piece to receiving tower
    bool makeMove(Tower* sender, Tower* receiver);

    void restart();

    bool hasPlayerWonGame();

    std::vector<Tower*> getTowers() const;

    void addMoveToUi(Ui::MainWindow ui);
    void clearMoveHistory();


private:
    std::vector <Tower*> towers_;
    std::vector<GameMove*> moveHistory_;

    int piecesPerTower;
    int amountOfTowers;

    QWidget* parent;
    Ui::MainWindow* ui_;
};

#endif // GAMEMANAGER_HH
