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
    explicit Piece(int size, qreal x, qreal y, qreal width, qreal height, QWidget *parent = nullptr);
    explicit Piece(int size, QPointF location, QSizeF pieceSize, QWidget* parent = nullptr);

    ~Piece() override;

    int getSize() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

    QWidget* getParent();

signals:

public slots:


private:
    QRectF* frame;
    int size_;
    qreal x_;
    qreal y_;
    qreal width_;
    qreal height_;

    QWidget* parent_;

};

#endif // PIECE_HH
