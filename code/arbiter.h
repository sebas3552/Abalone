#ifndef ARBITER_H
#define ARBITER_H

#include <QMap>
#include "board.h"
#include <algorithm>    // std::find
#include <QtDebug>

/**
 * @brief The Arbiter class represents a generic arbiter, that is, the object that must verify all the movements
 * done in the board.
 */
class Arbiter
{
    protected:

        ///pointer to the board manager (class)
        Board* board;

        ///Pointer to the actual board matrix
        vector<vector<Piece*>>* physicalBoard;

        ///Current player's piece color.
        Color current_player_color;

        ///Current player ID
        int currentPlayer;

        ///Spaces the current selected triad (if any) can mov
        vector<QPoint> canMoveList;

    public:

        /**
         * @brief Constructs the object.
         * @param board received a pointer to the main board object
         */
        Arbiter(Board* board): board(board)
        {}

        /**
         * Destroys the object.
         */
        virtual ~Arbiter(){}

        /**
         * @brief Validates if a given position is valid in the board.
         * @param pos Coordinate of the position to be validated.
         * @return True if the given position is valid in the board, false otherwise.
         */
        virtual bool isValidPos(QPoint pos) const = 0;

        /**
         * @brief Verifies if a given piece placed in a given position is able to move to another position.
         * @param from Source coordinate where the piece actually is.
         * @param to Destination of the movement in the board.
         * @return True if the piece is able to move to the destination point, false otherwise.
         */
        virtual bool canMove(QPoint from, QPoint to) const = 0;

        /**
         * @brief Changes the current player
         * @param owner current player id
         */
        virtual void setCurrentPlayer(int owner) = 0;

        /**
         * @brief Obtains the current player
         * @return owner current player id
         */
        virtual int getCurrentPlayer() = 0;

        /**
         * @brief Receives the input provided by the gamewindow and processes what to do with it.
         * @param selected_coordinates selected_coordinates by the user.
         */
        virtual int select(QPoint selected_coordinates) = 0;


        /**
         * @brief Updates the canMoveList to have the current possible moves for the last selected piece (if any).
         */
        virtual void updateCanMoveList() = 0;

        /**
         * @brief Checks whether the piece belongs to the current player.
         * @param selected_piece selected piece by the user.
         */
        virtual bool pieceBelongsToCurrentPlayer(QPoint selected_piece) = 0;

        /**
         * @brief Checks whether the piece belongs to the current player.
         * @param selected_piece selected piece by the user.
         */
        virtual bool pieceBelongsToCurrentPlayer(Piece selected_piece) = 0;

        /**
         * @brief Check whether the provided position is a movable position for the last piece selected
         * @param position_to_check position in the board to check
         */
        virtual bool checkCanMoveList(QPoint position_to_check) = 0;

        /**
         * @brief Tests whether the game is over or not.
         * @return The loser player id if any, or -1 otherwise.
         */
        virtual int isGameOver() const = 0;
};

#endif // ARBITER_H
