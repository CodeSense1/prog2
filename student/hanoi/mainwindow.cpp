#include "mainwindow.hh"
#include "ui_mainwindow.h"


#include "piece.hh"

#include <QString>

#include <iostream>

/*
 * Problems:
 *  Improve tower positioning
 *  Add dynamic scaling for piece height
 *  Pieces are currently too wide
 *
 *  Add timer
 *
 */


using buttonMapIterator = std::map<QPushButton, GameMove>::iterator;

// Restarting does not work
// New game crashes

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    connect(ui_->quitBtn, &QPushButton::clicked, this, [&]() {QApplication::quit();});
    dClock = new DigitalClock(this);

    connect(dClock, &DigitalClock::valueChanged, ui_->currentTime, [&]() {
        ui_->currentTime->setText(dClock->getElapsedTime()->toString("mm:ss"));
    });

    connect(dClock, &DigitalClock::onRestart, ui_->currentTime, [&]() {
        ui_->currentTime->setText(dClock->getElapsedTime()->toString("mm:ss"));
    });

    ui_->bestTime->setText("No best time yet");


    ui_->amountOfObjects->setText(QString::number(DEFAULT_PIECE_COUNT)); // Set default values
    ui_->errorLabel->setVisible(false); // No Error by default

    connect(ui_->restartBtn, &QPushButton::clicked, this, &MainWindow::Restart);
    connect(ui_->newGameBtn, &QPushButton::clicked, this, &MainWindow::NewGame);

    Initialize();
}


MainWindow::~MainWindow()
{
    // How to delete scene?
    delete manager_;
    delete ui_;
}

void MainWindow::Initialize()
{

    scene_ = new QGraphicsScene();
    ui_->gameWindow->setScene(scene_);
    ui_->gameWindow->setSceneRect(scene_->sceneRect());

    // Define gameManager
    manager_ = new GameManager(pieceCount_, DEFAULT_TOWER_COUNT, ui_->gameWindow);
    manager_->setUi(ui_);

    // Assign move to corresponding buttons
    connectButtons();





    // Prevent adding duplicates?
    scene_->clear();

    manager_->drawTowers(scene_);
    Update();

}

void MainWindow::connectButtons()
{
    buttonMoves_.clear(); // clear previous connections
    buttonMoves_.insert(std::pair<QPushButton*, GameMove>(ui_->ab, GameMove(manager_->getTowers(), 0, 1)));
    buttonMoves_.insert(std::pair<QPushButton*, GameMove>(ui_->ac, GameMove(manager_->getTowers(), 0, 2)));
    buttonMoves_.insert(std::pair<QPushButton*, GameMove>(ui_->ba, GameMove(manager_->getTowers(), 1, 0)));
    buttonMoves_.insert(std::pair<QPushButton*, GameMove>(ui_->bc, GameMove(manager_->getTowers(), 1, 2)));
    buttonMoves_.insert(std::pair<QPushButton*, GameMove>(ui_->ca, GameMove(manager_->getTowers(), 2, 0)));
    buttonMoves_.insert(std::pair<QPushButton*, GameMove>(ui_->cb, GameMove(manager_->getTowers(), 2, 1)));

    updateConnections();
}

void MainWindow::updateConnections()
{
    buttonMapIterator it;
    // Connect all logical pushbuttons to corresponding gamemove
    for (const auto& item : buttonMoves_) {

        item.first->disconnect(); // disconnect all previous connections
        // this ensures that button is connected to current game
        // If disconnect is not called, new game will not work
        // since connection is still in the old game

        connect(item.first, &QPushButton::clicked, this, [&]() {

            Tower* sender = item.second.getSender();
            Tower* receiver = item.second.getReceiver();
            manager_->makeMove(sender, receiver);


            if (manager_->hasPlayerWonGame()) {

                QTime* elapsedTime = dClock->getElapsedTime();
                if (bestTime == nullptr) {
                    bestTime = elapsedTime;
                    ui_->bestTime->setText(bestTime->toString("mm:ss"));

                }

                else if (elapsedTime < bestTime) {
                    // This is new best time
                    bestTime = elapsedTime;
                    ui_->bestTime->setText(bestTime->toString("mm:ss"));

                } else {
                    std::cout << elapsedTime->toString().toStdString() << std::endl;
                }

                // dClock->stop();

                gameWinText = scene_->addText("Congratulations! You won the game!");
                gameWinText->setFont(QFont("Comic Sans", 26));
                gameWinText->moveBy(0, -ui_->gameWindow->height()/2);
                return;
            }
            this->Update();
        });
    }
}

void MainWindow::NewGame()
{
     // Clear old buttons

    manager_->restart();
    pieceCount_ = ui_->amountOfObjects->text().toInt();

    if (pieceCount_ < 1) {
        ui_->errorLabel->setVisible(true);
        return;
    }

    ui_->errorLabel->setVisible(false);



    manager_ = new GameManager(pieceCount_, DEFAULT_TOWER_COUNT, ui_->gameWindow);
    manager_->setUi(ui_);

    // Update buttons
    connectButtons();
    dClock->restart();


    scene_ = new QGraphicsScene();
    ui_->gameWindow->setScene(scene_);
    ui_->gameWindow->setSceneRect(scene_->sceneRect());

    manager_->drawTowers(scene_);
    Update();


}

void MainWindow::Restart()
{
    // Reverse all moves
    // Reverses game state to the beginning

    if (scene_->items().contains(gameWinText))
        scene_->removeItem(gameWinText);

    manager_->restart();
    dClock->restart();

    // ui_->moveBoard->clear();
    Update();
}

void MainWindow::Update()
{

    // Toggle button state based on current game state
    for (auto& item : buttonMoves_) {
        item.first->setEnabled(item.second.isMoveValid());
    }
}
