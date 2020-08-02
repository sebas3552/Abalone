#include "piece.h"

Piece::Piece()
    : owner(-1), name(QString("")), color (Color::gray)
{}

Piece::Piece(int owner, QString name, Color color)
    : owner(owner), name(name), color(color)
{

}

Piece::~Piece() {}

void Piece::setOwner(int owner)
{
    this->owner = owner;
}

int Piece::getOwner() const
{
    return this->owner;
}

void Piece::setName(QString name)
{
    this->name = name;
}

QString Piece::getName() const
{
    return this->name;
}

void Piece::setColor(Color color)
{
    this->color = color;
}

Color Piece::getColor() const
{
    return this->color;
}
