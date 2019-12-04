#ifndef PIECE_HH
#define PIECE_HH

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>


#include <memory>

class Piece : public QGraphicsRectItem
{
public:
    explicit Piece(int size, int x, int y, int width, int height, QWidget *parent = nullptr);
    explicit Piece(int size, QPointF location, QSize pieceSize, QWidget* parent = nullptr);

    int getSize();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

    QWidget* getParent();

signals:

public slots:


private:
    QRectF* frame;
    int size_;
    int x_;
    int y_;
    int width_;
    int height_;

    QWidget* parent_;

};

#endif // PIECE_HH
