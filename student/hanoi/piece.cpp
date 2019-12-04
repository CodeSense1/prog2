#include "piece.hh"
#include "colormanager.hh"

Piece::Piece(int size, int x, int y, int width, int height, QWidget *parent)
  : size_(size), x_(x), y_(y), width_(width), height_(height), parent_(parent)

{
    frame = new QRectF(x, y, width, height);
    setFlag(ItemIsMovable);

}

// Optional constructor
Piece::Piece(int size, QPointF location, QSize pieceSize, QWidget *parent)
    : size_(size),
      x_(static_cast<int>(location.rx())),
      y_(static_cast<int>(location.ry())),
      width_(pieceSize.rwidth()),
      height_(pieceSize.rheight()),
      parent_(parent)
{
    frame = new QRectF(x_, y_, width_, height_);
    setFlag(ItemIsMovable);
}

int Piece::getSize()
{
    return size_;
}


void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush( colorManager::getRandomColor() );

    painter->fillRect(rect, brush);
    painter->drawRect(rect);


}

QRectF Piece::boundingRect() const
{
    return *frame;
}

QWidget *Piece::getParent()
{
    return this->parent_;
}
