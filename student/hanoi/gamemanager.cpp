
#include "gamemanager.hh"
#include "piece.hh"
#include <QGraphicsItem>
#include <QListWidgetItem>

#include <iostream>

using towerIterator = std::vector<Tower*>::iterator;

GameManager::GameManager(int piecesPerTower, int amountOfTowers, QWidget *widget)
    :piecesPerTower(piecesPerTower),
     amountOfTowers(amountOfTowers), parent(widget)
{
    // Calculate dynamic object size?
    // It might not be very useful for drag and drop, but hey _/

    int towerSpacing = parent->width()/amountOfTowers;

    for (int i = 0; i < amountOfTowers; i++) {
        QPointF towerPoint(i*towerSpacing,
                           -parent->geometry().height());
        Tower* tower = new Tower(piecesPerTower,i+1, towerPoint, parent);

        if (i == 0) {
            for (int j = piecesPerTower; j > 0; j--) {

                double blockSize = tower->boundingRect().height()/piecesPerTower *0.9;
                double grid = j*blockSize*0.7;
                QPointF blockOffset(
                        towerPoint.x() - grid/2
                        + tower->boundingRect().width()/2,
                        towerPoint.y()
                        + tower->boundingRect().height()
                        -(piecesPerTower+1)*blockSize + grid*(1/0.7));


                Piece* newPiece = new Piece(j, blockOffset,
                                            QSizeF(grid, blockSize), parent);
                tower->addPiece(newPiece);
            }
        }

        towers_.push_back(tower);

    }
}

GameManager::~GameManager()
{
    delete parent;

    for (auto& tower : towers_) {
        delete tower;
        tower = nullptr;
    }
}

void GameManager::setUi(Ui::MainWindow *ui)
{
    ui_ = ui;
}

void GameManager::drawTowers(QGraphicsScene *scene)
{
    // Adds all towers and pieces to current scene
    for(auto tower : towers_) {

        scene->addItem(tower);
        tower->drawPieces(scene);


        // Scene has this item already, no need to add that to the scene
    }
}

bool GameManager::makeMove(int sender, int receiver)
{
    /*
     * Makes a move on the board. Returns true,
     * if move is legal and it was executed succesfully
     *
     * ie. calls movePiece for sender-tower
     *
     * param:
     *  sender: INT, id of the tower which moves top piece to receiving tower
     *  receiver: INT, id of the tower where top piece is moved
     *
     * return: true, if moving was succesful
     */

    if ( (sender -1 < 0) | (receiver -1 < 0) ) {
        // Errorreus tower id
        return false;
    }

    Tower* senderTower = towers_.at(static_cast<unsigned>(sender-1));
    Tower* receiverTower = towers_.at(static_cast<unsigned>(receiver-1));

    moveHistory_.insert(moveHistory_.begin(),
                        new GameMove(senderTower, receiverTower));

    ui_->moveBoard->addItem(QString::number(moveHistory_.size())
                                    + ": "
                                    + moveHistory_.front()->toString()+ "\n");

    ui_->moveBoard->scrollToBottom();

    senderTower->moveTopPieceTo(receiverTower);


    return true;
}

bool GameManager::makeMove(Tower *sender, Tower *receiver)
{
    // Overloaded method
    /*
     * Makes a move on the board. Returns true,
     * if move is legal and it was executed succesfully
     *
     * ie. calls movePiece for sender-tower
     *
     * param:
     *  sender: Tower*, Pointer to sender-tower
     *  receiver: Tower*, Pointer to receiving tower
     *
     * return: true, if moving was succesful
     */
    if (sender->moveTopPieceTo(receiver)) {

        moveHistory_.insert(moveHistory_.begin(),
                            new GameMove(sender, receiver));

        ui_->moveBoard->addItem(QString::number(moveHistory_.size())
                                        + ": "
                                        + moveHistory_.front()->toString()+ "\n");
        ui_->moveBoard->scrollToBottom();

        return true;
    }

    return false;
}

void GameManager::restart()
{
    for (const auto& move : moveHistory_) {
        move->reverseMove();
    }

    clearMoveHistory();

}

bool GameManager::hasPlayerWonGame()
{

    for (size_t i = 1; i < towers_.size(); i++) {
        if (towers_.at(i)->getPieces().size() ==
                static_cast<unsigned>(piecesPerTower)) {
            return true;
        }
    }

    return false;

}

std::vector<Tower *> GameManager::getTowers() const
{
    return towers_;

}


void GameManager::clearMoveHistory()
{
    moveHistory_.clear();
    ui_->moveBoard->clear();

}
