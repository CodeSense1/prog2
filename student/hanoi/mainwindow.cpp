#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>

#include "tower.hh"
#include "piece.hh"

#include <QString>

#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->quitBtn, &QPushButton::clicked, this, [&]() {this->close();});

    scene_ = new QGraphicsScene();
    ui->gameWindow->setScene(scene_);
    ui->gameWindow->setSceneRect(scene_->sceneRect());

    ui->amountOfObjects->setText(QString::number(DEFAULT_PIECE_COUNT)); // Set default values

    connect(ui->restartBtn, &QPushButton::clicked, this, &MainWindow::StartGame);
    connect(ui->newGameBtn, &QPushButton::clicked, this, &MainWindow::Restart);


    // This could be improved with QButtonGroup and QAbstractButton,
    // but I cannot figure out how...
    connect(ui->ab, &QPushButton::clicked, this, [&](){
        manager->makeMove(tower1Id, tower2Id);
    });

    connect(ui->bc, &QPushButton::clicked, this, [&](){
        manager->makeMove(tower2Id, tower3Id);
    });

    connect(ui->ac, &QPushButton::clicked, this, [&](){
        manager->makeMove(tower1Id, tower3Id);

    });
    connect(ui->ba, &QPushButton::clicked, this, [&](){
        manager->makeMove(tower2Id, tower1Id);
    });
    connect(ui->ca, &QPushButton::clicked, this, [&](){
        manager->makeMove(tower3Id, tower1Id);
    });
    connect(ui->cb, &QPushButton::clicked, this, [&](){
        manager->makeMove(tower3Id, tower2Id);
    });

    StartGame();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartGame()
{
    scene_->clear();
    if (pieceCount < 1) {
        // Give some error message, that there should be at least one piece
    }
    manager = new GameManager(pieceCount, DEFAULT_TOWER_COUNT, ui->gameWindow);
    manager->drawTowers(scene_);
}

void MainWindow::Restart()
{
    pieceCount = ui->amountOfObjects->text().toInt();
    StartGame();
}
