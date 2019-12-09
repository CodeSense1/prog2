/*
 * Author: Joonas Kakkuri
 * Student id: 274166
 * email: joonas.kakkuri@tuni.fi
 *
 *
 * Tower class inherits QGraphicsItem, and therefore
 * it can be added to QGraphicsView.
 *
 * Main purpose is to hold data about pieces and
 * rules about how to move them.
 *
 * Tower is also responsible for drawing itself and its pieces to scene
 *
 */

#include "tower.hh"
#include "colormanager.hh"
#include "gamemove.hh"

#include <QPointF>

#include <iostream>

Tower::Tower(int maxPieces, QPointF location, QWidget *parent) :
    maxPieces_(maxPieces), towerId_(-1), location_(location), parent(parent)
{
    maxPieceWidth = parent->width()/maxPieces_;
    stick = new QRectF(location,
                       QSize(TOWER_WIDTH,
                             static_cast<int>(parent->height()* 0.8) ));
}

Tower::Tower(int maxPieces, int towerId, QPointF location, QWidget *parent) :
    maxPieces_(maxPieces), towerId_(towerId), location_(location), parent(parent)
{
    maxPieceWidth = parent->width()/maxPieces_;
    stick = new QRectF(location,
                       QSize(TOWER_WIDTH,
                             static_cast<int>(parent->height()* 0.8) ));
}

Tower::~Tower()
{
    /*delete stick;
    delete parent;

    for (auto& piece : pieces) {
        delete piece;
    }

    std::cout << "Tower deconstructed succesfully" << std::endl;*/
}

bool Tower::addPiece(Piece *pieceToAdd)
{
    /*
     * Adds new piece to this tower
     *
     * param:
     *  piceToAdd - pointer to Piece-object that we want to add
     *
     * return:
     *  true, if adding was succesful
     *
     */
    pieces.push_back(pieceToAdd);
    return true;
}

void Tower::drawPieces(QGraphicsScene *scene)
{
    // Adds all pieces to scene
    // param:
    //  scene: pointer to scene
    //
    // return: void
    for (auto piece : pieces) {
        scene->addItem(piece);
    }
}

void Tower::removePieceFromTop()
{
    pieces.pop_back();
}

bool Tower::moveTopPieceTo(Tower *other)
{

    GameMove move(this, other);

    if (!move.isMoveValid())
        return false;
    Piece* pieceToMove = getTopPiece();


    // Calculate vectors for x and y coordinate
    qreal dy = (this->pieces.size()-1)
            *pieceToMove->boundingRect().height()
            - (other->pieces.size())
            *pieceToMove->boundingRect().height();

    qreal dx = other->boundingRect().x() - boundingRect().x();

    // Move the top piece of the tower
    // and update parent-child relationships
    pieceToMove->moveBy(dx, dy);
    pieceToMove->setParentItem(other);

    other->addPiece(pieceToMove);
    this->pieces.pop_back();

    return true;

}

Piece *Tower::getTopPiece()
{
    // Returns top piece of the tower
    // If tower is empty, default piece is returned
    // with highest possible piecesize
    if (pieces.size() == 0) {
        return new Piece(MAX_PIECE_SIZE, 0,0,0,0, parent);
    }
    return pieces.back();
}

std::vector<Piece *> Tower::getPieces()
{
    // Get all pieces that are child of this tower-object
    return pieces;
}


void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    /*
     * Paints Tower-object on the scene
     *
     * param:
     *  painter: pointer to painter -object
     *  options: style options
     *  widget: parent widget
     *
     * return: void
     *
     */
    QRectF rect = boundingRect();
    QBrush brush( colorManager::getRandomColor() );
    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

QRectF Tower::boundingRect() const
{
    // Return Tower-object bounding rectangle
    return *stick;
}

int Tower::getTowerId()
{
    return towerId_;
}


