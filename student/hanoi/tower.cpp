#include "tower.hh"
#include "colormanager.hh"
#include <QPointF>

#include <iostream>

Tower::Tower(int maxPieces, QPoint location, QWidget *parent) :
  maxPieces_(maxPieces), location_(location), parent(parent)
{
    maxPieceWidth = parent->width()/maxPieces_;
    stick = new QRectF(location, QSize(TOWER_WIDTH, static_cast<int>(parent->height()) * 0.8));
}

bool Tower::addPiece(Piece *pieceToAdd)
{
    pieces.push_back(pieceToAdd);
    return true;
}

void Tower::drawPieces(QGraphicsScene *scene)
{
    for (auto piece : pieces) {
        scene->addItem(piece);
    }
}

bool Tower::moveTopPieceTo(Tower *other)
{
    if (pieces.size() == 0) {
        // No pieces
        return false; // FIX THIS
    }

    Piece* pieceToMove = pieces.back();

    if (pieceToMove->getSize() > other->getTopPiece()->getSize()) {
        // Illegal move
        return false;
    }


    qreal dy = (this->pieces.size()-1)*pieceToMove->boundingRect().height() - (other->pieces.size())*pieceToMove->boundingRect().height();
    qreal dx = other->boundingRect().x() - boundingRect().x(); // x-coordinate for position vector

    pieceToMove->moveBy(dx, dy);
    //pieceToMove->setPos(dx, dy);
    pieceToMove->setParentItem(other);

    other->addPiece(pieceToMove);
    this->pieces.pop_back();

    std::cout << "Piece moved succesfully" << std::endl;

    // This piece is smaller than other tower size

    return true;

}

Piece *Tower::getTopPiece()
{
    if (pieces.size() == 0) {
        return new Piece(MAX_PIECE_COUNT, 0,0,0,0, parent);
    }
    return pieces.back();
}

std::vector<Piece *> Tower::getPieces()
{
    return pieces;
}


void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{

    QRectF rect = boundingRect();
    QBrush brush( colorManager::getRandomColor() );
    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

QRectF Tower::boundingRect() const
{
    return *stick;
}


