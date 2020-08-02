#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"

/**
 * @brief The Player class represents a player of the game class.
 */
class Player
{
    protected:

        ///ID of the player.
        int id;

        ///Color that represents the player.
        Color color;

    public:

        /**
         * @brief Constructs the object.
         */
        Player();

        /**
         * @brief Constructs the object with specified parameters.
         * @param id Int that represents ID player.
         * @param color Color that represents player's color.
         */
        Player(int id, Color color);

        /**
         * @brief Sets the player's ID.
         * @param id ID of this player.
         */
        void setId(int id);

        /**
         * @brief Sets the player's color.
         * @param color Color that represents the player.
         */
        void setColor(Color color);

        /**
         * @brief Returns the player's ID.
         * @return An int that represents the player's ID.
         */
        int getId();

        /**
         * @brief Returns the player's color.
         * @return A Qt::GlobalColor color that represents the player's color's pieces.
         */
        Color getColor();
};

#endif // PLAYER_H
