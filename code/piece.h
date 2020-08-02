#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include "saveable.h"

typedef Qt::GlobalColor Color;

/**
 * @brief The Piece class represents a board game piece.
 * Inherits from Saveable.
 */
class Piece : public Saveable
{
    protected:

        ///Player that owns the piece.
        int owner;

        ///String containing the piece name.
        QString name;

        ///Piece color.
        Color color;

    public:

        /**
         * @brief Constructs the object.
         */
        Piece();

        /**
         * @brief Constructs the object with specified parameters.
         * @param owner Player that owns the piece.
         * @param name String containing the piece name.
         * @param color Piece color.
         */
        Piece(int owner, QString name, Color color);

        /**
         * @brief Destroys the object.
         */
        virtual ~Piece();

        /**
         * @brief Sets the piece's owner.
         * @param owner Player that owns the piece.
         */
        void setOwner(int owner);

        /**
         * @brief Returns the piece owner.
         * @return An int that represents the player that owns the piece.
         */
        int getOwner() const;

        /**
         * @brief Sets the piece name.
         * @param name String containing the piece name.
         */
        void setName(QString name);

        /**
         * @brief Returns the piece name.
         * @return String containing the piece name.
         */
        QString getName() const;

        /**
         * @brief Sets the piece color.
         * @param color Piece color.
         */
        void setColor(Color color);

        /**
         * @brief Returns the piece color.
         * @return Piece color.
         */
        Color getColor() const;
};

#endif // PIECE_H
