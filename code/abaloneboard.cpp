#include "abaloneboard.h"

//#define qDebug QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug //for debugging

AbaloneBoard::AbaloneBoard(size_t rows, size_t columns)
: Board(rows, columns)
{}

AbaloneBoard::~AbaloneBoard()
{
    for(size_t i = 0; i < this->rows; ++i)
        for(size_t j = 0; j < this->columns; ++j)
            if(this->board[i][j])
                delete this->board[i][j];
}

void AbaloneBoard::addPiece(Piece* piece, QPoint pos)
{;
    board[static_cast<size_t>(pos.y())][static_cast<size_t>(pos.x())] = piece;
}

void AbaloneBoard::addPiece(QPoint pos, int owner, QString name, Color color)
{
    Piece* piece_to_add = new Piece(owner, name, color);
    board[static_cast<size_t>(pos.y())][static_cast<size_t>(pos.x())] = piece_to_add;
}

void AbaloneBoard::addLostPiece(Piece *piece)
{
    lostPieces.push_back(piece);
}

void AbaloneBoard::removePiece(QPoint pos)
{
    //delete board[static_cast<size_t>(pos.y())][static_cast<size_t>(pos.x())]; //SEGMENTATION FAULT
    board[static_cast<size_t>(pos.y())][static_cast<size_t>(pos.x())] = nullptr;
}

void AbaloneBoard::movePiece(QPoint from, QPoint to) //Only to nullptr places
{
    qDebug() << "movePiece: MOVING a piece from " << from << " to " << to << endl;
    board[static_cast<size_t>(to.y())][static_cast<size_t>(to.x())] = getPiece(from);
    removePiece(from);
}


Piece* AbaloneBoard::getPiece(QPoint input_coordinates)
{
    return board[static_cast<size_t>(input_coordinates.y())][static_cast<size_t>(input_coordinates.x())];
}

vector<Piece*> AbaloneBoard::getLostPieces()
{
    return lostPieces;
}


