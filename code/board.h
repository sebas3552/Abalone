#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <QPoint>
#include <vector>

#include "piece.h"
#include "saveable.h"

using namespace std;

/**
 * @brief The Board class defines an abstract type of board.
 * Inherits from Saveable.
 */
class Board : public Saveable
{

    protected:

        ///Holds the collection of pieces in the board.
        vector<Piece*> pieces;

        ///The proper matrix that represents a board, containing pointers to pieces.
        vector<vector<Piece*>> board;

        ///Number of rows of the board.
        size_t rows;

        ///Number of columns of the board.
        size_t columns;

        ///The player playing his turn
        int currentPlayer;

    public:

        /**
         * @brief Constucts the object.
         */
        Board()
        : rows(0), columns(0)
        {}

        /**
         * @brief Construct the object with specified parameters
         * @param rows Desired number of rows for the board.
         * @param columns Desired number of columns for the board.
         */
        Board(size_t rows, size_t columns)
        : rows(rows), columns(columns)
        {
            //Initializes the board matrix with null pointers.
            board = vector<vector<Piece*>>(rows, vector<Piece*>(columns, nullptr));
        }

        /**
         * @brief Destroys the object.
         */
        virtual ~Board() {}

        /**
         * @brief Adds a piece to the board in a given position.
         * @param piece Pointer to the piece being added.
         * @param pos Coordinate to place the piece.
         */
        virtual void addPiece(Piece* piece, QPoint pos) = 0;

        /**
         * @brief Removes a piece placed in the given position.
         * @param pos Coordinate in the board where the piece being removed is placed.
         */
        virtual void removePiece(QPoint pos) = 0;

        /**
         * @brief Moves a piece from a given point to another in the board.
         * @param from Source coordinate where the piece being moved actually is.
         * @param to Destination of the movement in the board.
         */
        virtual void movePiece(QPoint from, QPoint to) = 0;

        /**
         * @brief Provides a copy of the physical board
         * @return the board object.
         */
        virtual vector<vector<Piece*>> getBoard() const { return this->board; }

};

#endif // BOARD_H
