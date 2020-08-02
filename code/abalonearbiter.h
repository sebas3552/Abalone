#ifndef ABALONEARBITER_H
#define ABALONEARBITER_H

#include <QMap>
#include "arbiter.h"
#include <algorithm>    // std::find
#include <QtDebug>
#include "abaloneboard.h"

///Maximum size of any Abalone board row or column.
#define DEFAULT_SIZE 9
#define GAME_NOT_OVER -1
#define PLAYER_1_GAME_OVER 0
#define PLAYER_2_GAME_OVER 1

/**
 * @brief The AbaloneArbiter class represents the judge (or arbiter) that knows the rules of the game and responds to player's requests (selects) accordingly
 * Inherits from Arbiter.
 */

class AbaloneArbiter : public Arbiter
{
    friend class Controller;
    friend class AbaloneSaver;

    private:

        ///Holds the pieces selected by the user, from 1 to 3.
        vector<QPoint> currentTriad;

        ///Holds the pieces to be pushed in a conflict scenario (if any).
        vector<QPoint> oppositeTriad;

        ///Type of movement, either strong or weak (strong if the movement is in the same direction than the triad).
        bool strongMovement;

        ///Enum to represent all the different movements a player can make.
        enum direction {dNone, dHorizontalRight, dHorizontalLeft,dSlantedRightUp,dSlantedRightDown,dSlantedLeftUp,dSlantedLeftDown}; // d = direction, Horizontal right, horizontal left, slanted right up, slanted right down, slanted left up, slanted left down

         ///Enum to represent the different types of results that can appear when testing a piece in the conflict scenario
        enum type_of_piece {pEmpty, pInvalid, pEnemy, pOwn}; //when testing conflict if the piece in the cordinate is empty, an enemy or an own piece from the player.

        ///Point objects to represent all the different movements a player can make.
        const QPoint None = QPoint(0,0);
        const QPoint HorizontalRight = QPoint(1,0);
        const QPoint HorizontalLeft = QPoint(-1,0);
        const QPoint SlantedRightUp = QPoint(1,-1);
        const QPoint SlantedRightDown = QPoint(0,1);
        const QPoint SlantedLeftUp = QPoint(0,-1);
        const QPoint SlantedLeftDown = QPoint(-1,1);

        ///Map that joins together all the possible directions for pieces.
        QMap<direction,QPoint> directionMap;

        ///Direction arrat to figure out all the adjacent pieces to the one being tested.
        vector<QPoint> directionArray;

    public:


        /**
         * @brief Constructs the object.
         * @param board received a pointer to the main board object
         */
        AbaloneArbiter(AbaloneBoard* board);

        /**
         * Destroys the object.
         */
        ~AbaloneArbiter();       

        /**
         * @brief Validates if a given position is valid in the board.
         * @param pos Coordinate of the position to be validated.
         * @return True if the given position is valid in the board, false otherwise.
         */
        virtual bool isValidPos(QPoint pos) const;

        /**
         * @brief Verifies if a given piece placed in a given position is able to move to another position.
         * @param from Source coordinate where the piece actually is.
         * @param to Destination of the movement in the board.
         * @return True if the piece is able to move to the destination point, false otherwise.
         */
        virtual bool canMove(QPoint from, QPoint to) const;

        /**
         * @brief Changes the current player
         * @param owner current player id
         */
        virtual void setCurrentPlayer(int owner);

        /**
         * @brief Obtains the current player
         * @return owner current player id
         */
        virtual int getCurrentPlayer();

        /**
         * @brief Asks wether a given triad of pieces is able to move from a given position to another
         * position.
         * @param to Destination of the triad movement.
         * @return True if the triad is able to move to the destination point, false otherwise.
         */

        bool canMoveTriad(QPoint to);

        /**
         * @brief Compares two adjacent positions to obtain the movement direction.
         * @param one the position of the first piece.
         * @param two the positon of the second piece.
         * @return Returns a direction enum with the direction of the piece "one" moving to the "two" spot.
         */
        direction pairDirection(QPoint one, QPoint two);

        /**
         * @brief Figures out the overall direction of a triad.
         * @return The overall direction of the triad based on the direction enum.
         */
        direction triadDirection();

        /**
         * @brief Receives the input provided by the gamewindow and modifies currentTriad as result.
         * @param selected_piece selected piece by the user.
         */
        virtual int select(QPoint selected_coordinates);

        /**
         * @brief Tests whether a piece can be added to the triad or not and does it if possible.
         * @param selected_coordinates piece to try to add to the triad.
         */
        void tryToAddPieceToTriad(QPoint piece_to_add);

        /**
         * @brief Updates the canMoveList to have the current possible moves for the last selected piece (if any).
         */
        virtual void updateCanMoveList();

        /**
         * @brief Tests whether two pieces are contigous to one another.
         * @param one first piece.
         * @param two second piece.
         */
        bool contiguous(QPoint one, QPoint two);

        /**
         * @brief Checks whether the piece belongs to the current player.
         * @param selected_piece selected piece by the user.
         */
        virtual bool pieceBelongsToCurrentPlayer(QPoint selected_piece);

        /**
         * @brief Checks whether the piece belongs to the current player.
         * @param selected_piece selected piece by the user.
         */
        virtual bool pieceBelongsToCurrentPlayer(Piece selected_piece);

        /**
         * @brief Check whether the provided position is a movable position for the last piece selected
         * @param position_to_check position in the board to check
         */
        virtual bool checkCanMoveList(QPoint position_to_check);

        /**
         * @brief Move the triad, should have already been checked it is a valid move by canMoveTriad.
         * @param to position in the board to check.
         */
        void moveTriad(QPoint to);

        /**
         * @brief Returns what type of piece has been found: empty, invalid, enemy or own.
         * @param coordinates_to_check position in the board to check.
         */
        AbaloneArbiter::type_of_piece determineTypeOfPiece(QPoint coordinates_to_check) const;

        /**
         * @brief Returns what type of piece has been found: empty, invalid, enemy or own.
         * @param beginning_of_opposite_triad the start of the opposite triad.
         */
        void formOppositeTriad(QPoint beginning_of_opposite_triad);

        /**
         * @brief Tests whether the game is over or not.
         * @return The loser player id if any, or -1 otherwise.
         */
        virtual int isGameOver() const;

        /**
         * @brief Prints the structure's state, for debugging purposes.
         */
        void printStructuresState();
};

#endif // ABALONEARBITER_H
