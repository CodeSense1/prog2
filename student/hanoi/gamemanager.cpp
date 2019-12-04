
#include "gamemanager.hh"
#include "piece.hh"
#include <QGraphicsItem>

GameManager::GameManager(int piecesPerTower, int amountOfTowers, QWidget *widget)
    :piecesPerTower(piecesPerTower), amountOfTowers(amountOfTowers), parent(widget)
{
    int towerSpacing = parent->width()/amountOfTowers;
    int offset = towerSpacing/2;

    for (int i = 0; i < amountOfTowers; i++) {
        QPoint towerPoint(i*towerSpacing + offset, static_cast<int>(-parent->geometry().height()));
        Tower* tower = new Tower(piecesPerTower, towerPoint, parent);

        if (i == 0) {
            for (int j = piecesPerTower; j > 0; j--) {
                int blockSize = 40;
                int grid = j*blockSize;
                QPoint blockOffset(
                        towerPoint.x() - grid/2
                            + static_cast<int>(tower->boundingRect().width()/2)
                            , towerPoint.y() + tower->boundingRect().height() -(piecesPerTower+1)*blockSize + grid);


                Piece* newPiece = new Piece(j, blockOffset, QSize(grid, blockSize), parent);
                tower->addPiece(newPiece);
            }
        }

        towers.push_back(tower);

    }
}

GameManager::~GameManager()
{
    delete parent;

    for (auto& tower : towers) {
        delete tower;
        tower = nullptr;
    }

}

void GameManager::drawTowers(QGraphicsScene *scene)
{
    // Adds all towers and pieces to current scene
    for(auto tower : towers) {
        scene->addItem(tower);
        tower->drawPieces(scene);
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

    if (sender -1 < 0 | receiver -1 < 0) {
        // Errorreus tower id
        return false;
    }

    towers.at(static_cast<unsigned>(sender-1))
            ->moveTopPieceTo(towers.at(static_cast<unsigned> (receiver-1)));


    return true;
}
