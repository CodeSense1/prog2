#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPushButton>
#include <QAbstractButton>

#include <memory>

#include "tower.hh"
#include "gamemanager.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void StartGame();
    void Restart();

protected:

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;
    GameManager* manager;

    const int DEFAULT_PIECE_COUNT = 3;
    const int DEFAULT_TOWER_COUNT = 3;

    const int tower1Id = 1;
    const int tower2Id = 2;
    const int tower3Id = 3;


    int pieceCount = DEFAULT_PIECE_COUNT;
};
#endif // MAINWINDOW_H
