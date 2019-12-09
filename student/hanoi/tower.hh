#ifndef TOWER_HH
#define TOWER_HH

// QT-imports
#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QPointF>

// STL- imports
#include <vector>


#include "piece.hh"

class GameMove;

class Tower : public QGraphicsItem
{
public:
    explicit Tower(int maxPieces, QPointF location, QWidget *parent = nullptr);
    explicit Tower(int maxPieces, int towerId, QPointF location, QWidget *parent = nullptr);

    ~Tower() override;
    bool addPiece(Piece* pieceToAdd);
    void drawPieces(QGraphicsScene* scene);

    void removePieceFromTop();
    bool moveTopPieceTo(Tower* other);

    Piece* getTopPiece();

    std::vector<Piece *> getPieces();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;




    int getTowerId();

signals:

public slots:

private:

    const int TOWER_WIDTH = 5;
    const int MAX_PIECE_SIZE = INT_MAX;
    std::vector< Piece* > pieces;

    QRectF* stick;
    int maxPieces_;
    int towerId_;
    QPointF location_;
    QWidget* parent;

    int maxPieceWidth;



};

#endif // TOWER_HH
