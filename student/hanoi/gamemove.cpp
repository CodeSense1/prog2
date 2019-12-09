#include "gamemove.hh"



GameMove::GameMove(Tower *sender, Tower *receiver)
    : sender_(sender), receiver_(receiver)
{

}

GameMove::GameMove(std::vector<Tower *> towers, int senderId, int receiverId)

{
    sender_ = towers.at(static_cast<unsigned>(senderId));
    receiver_ = towers.at(static_cast<unsigned>(receiverId));
}

Tower* GameMove::getSender() const {
    return sender_;
}

Tower* GameMove::getReceiver() const {
    return receiver_;
}

bool GameMove::isMoveValid() {

    if (sender_->getPieces().size() == 0) {
        return false;
    }

    Piece* pieceToMove = sender_->getTopPiece();

    if (pieceToMove->getSize() > receiver_->getTopPiece()->getSize()) {
        // Illegal move, piece is too big
        return false;
    }

    return true;
}

void GameMove::reverseMove()
{
    receiver_->moveTopPieceTo(sender_);
}

QString GameMove::toString() {

    return "Tower " + QString::number(sender_->getTowerId()) +
            " -> " +
            "Tower " + QString::number(receiver_->getTowerId());
}

