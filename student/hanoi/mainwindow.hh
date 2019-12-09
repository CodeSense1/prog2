#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPushButton>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QTime>

#include <memory>
#include <map>
#include <vector>

#include "tower.hh"
#include "gamemanager.hh"
#include "gamemove.hh"
#include "digitalclock.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Initialize();

    void connectButtons();
    void updateConnections();

    void NewGame();
    void Restart();
    void Update();

protected:

private:
    Ui::MainWindow *ui_;
    QGraphicsScene* scene_;
    GameManager* manager_;
    QButtonGroup logicalButtons_;

    QGraphicsTextItem* gameWinText;
    DigitalClock* dClock;
    QTime* bestTime = nullptr;

    std::map<QPushButton*, GameMove> buttonMoves_;
    // std::vector<GameMove*> moveHistory;

    const int DEFAULT_PIECE_COUNT = 4;
    const int DEFAULT_TOWER_COUNT = 3;

    const int tower1Id = 1;
    const int tower2Id = 2;
    const int tower3Id = 3;


    int pieceCount_ = DEFAULT_PIECE_COUNT;
};
#endif // MAINWINDOW_H
