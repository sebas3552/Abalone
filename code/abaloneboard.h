#ifndef ABALONEBOARD_H
#define ABALONEBOARD_H

#include <QMap>
#include "board.h"
#include <algorithm>    // std::find
#include <QtDebug>

///Maximum size of any Abalone board row or column.
#define DEFAULT_SIZE 9

/**
 * @brief The AbaloneBoard class represents an abalone specific board.
 * Inherits from Board.
 */
class AbaloneBoard : public Board
{
    friend class Controller;
    friend class AbaloneSaver;

    private:
        ///Current player's piece color.
        Color current_player_color;

        ///Holds the pieces that came off the board.
        vector<Piece*> lostPieces;

    public:

        /**
         * @brief Constructs the object.
         * @param rows Number of rows in the squared board.
         * @param columns Number of columns in the squared board.
         */
        AbaloneBoard(size_t rows = DEFAULT_SIZE, size_t columns = DEFAULT_SIZE);

        /**
         * Destroys the object.
         */
        ~AbaloneBoard();

        /**
         * @brief Adds a piece to the board in a given coordinate.
         * @param piece Pointer to the piece being added.
         * @param pos Coordinate to place the new piece in the board.
         */
        virtual void addPiece(Piece* piece, QPoint pos);

        /**
         * @brief Overloaded version to create the piece being added.
         * @param pos Coordinate to place the new piece in the board.
         * @param owner Player that owns the piece being added.
         * @param name Name of the piece.
         * @param color Color of the piece.
         */
        virtual void addPiece(QPoint pos, int owner, QString name, Color color);

        /**
         * @brief Adds a lost piece to the board piece set.
         * @param piece The piece to be added to the lost pieces set.
         */
        void addLostPiece(Piece* piece);

        /**
         * @brief Removes a piece placed in the given position.
         * @param pos Coordinate in the board where the piece being removed is placed.
         */
        virtual void removePiece(QPoint pos);

        /**
         * @brief Moves a piece from a given point to another in the board.
         * @param from Source coordinate where the piece being moved actually is.
         * @param to Destination of the movement in the board.
         */
        virtual void movePiece(QPoint from, QPoint to);

        /**
         * @brief Turns a QPoint into a Piece*
         * @param input_coordinates coordinates to get the piece from.
         */
        Piece* getPiece(QPoint input_coordinates);


        vector<Piece*> getLostPieces();

};

#endif // ABALONEBOARD_H
