#ifndef TOWER_HH
#define TOWER_HH

#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QPoint>

#include <memory>
#include <vector>

#include "piece.hh"

class Tower : public QGraphicsItem
{
public:
    explicit Tower(int maxPieces, QPoint location, QWidget *parent = nullptr);

    bool addPiece(Piece* pieceToAdd);
    void drawPieces(QGraphicsScene* scene);

    void removePieceFromTop();
    bool moveTopPieceTo(Tower* other);

    Piece* getTopPiece();

    std::vector<Piece *> getPieces();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;


signals:

public slots:

private:

    const int TOWER_WIDTH = 5;
    const int MAX_PIECE_COUNT = 25; // It's not practical to play with more than 25 pieces
    std::vector< Piece* > pieces;

    QRectF* stick;
    int maxPieces_;
    QPoint location_;
    QWidget* parent;

    int maxPieceWidth;



};

#endif // TOWER_HH
