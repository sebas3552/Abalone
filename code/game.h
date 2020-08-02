#ifndef GAME_H
#define GAME_H

#include <memory>
#include <QString>
#include <vector>

#include "board.h"
#include "saveable.h"
#include "saver.h"
#include "piece.h"
#include "arbiter.h"

///Forward declarations to avoid circular including problem.
class Board;
class GameLoader;

/**
 * @brief The Game class defines an abstract board game.
 * Inherits from Saveable.
 */
class Game : public Saveable
{

    protected:
        ///Pointer to the game's arbiter
        Arbiter* arbiter;

        ///Pointer to the game's board object.
        Board* board;

        ///Identifies the current player.
        int currentPlayer;

    public:

        ///Pointer to the game's loader.
        GameLoader * gameLoader;

        /**
         * @brief Destroys the object.
         */
        virtual ~Game() {}

        /**
         * @brief Initializes all requirements needed before starting the game.
         */
        virtual void init() = 0;

        /**
         * @brief Performs termination tasks upon game termination.
         */
        virtual void finalize() = 0;

        /**
         * @brief Does the necessary things when a player has won the game.
         */
        virtual int won() = 0;

        /**
         * @brief Does the necessary things when a player has lost the game.
         */
        virtual int gameOver() = 0;

        /**
         * @brief Shows the game rules.
         * @return A QString containing the game rules.
         */
        virtual QString showRules() = 0;

        /**
         * @brief Getter method for the game board.
         * @return A pointer to the board.
         */
        virtual Board * getBoard()
        {
            return board;
        }

        virtual Arbiter* getArbiter()
        {
            return arbiter;
        }

        /**
         * @brief Starts the game.
         * @param initialPlayer Player that starts the game, by default, player 0.
         */
        virtual void play(int initialPlayer) = 0;

        /**
         * @brief Allows a player to select a color for his pieces.
         * @param player Player id
         * @param color Color selected by the player.
         */
        virtual void chooseColor(int player, Color color)
        {
            Q_UNUSED(player);
            Q_UNUSED(color);
        }

        /**
         * @brief Saves the game with a given saver object.
         * @param saver Pointer to the saver object to save the game.
         */
        virtual void save(Saver* saver, QString fileName)
        {
            vector<Saveable*> objects;
            this->represent(objects);
            saver->save(objects, fileName);
        }

        /**
         * @brief Loads the state of the game saved in a file.
         * @param fileName Name of the file where the game was previously saved.
         * @return A pointer to a Game object builded from the file.
         */
        virtual Game * load(QString fileName) = 0;

        /**
         * @brief Returns the player's pieces color.
         * @param player Selected player.
         * @return The pieces color.
         */
        virtual Color getColor(int player) = 0;

        /**
         * @brief Gives the player's identifier of the actual turn in the game.
         * @return Player's identifier.
         */
        virtual int getCurrentPlayer() const
        {
            return this->currentPlayer;
        }

        /**
         * @brief Allows to set the player's turn.
         * @param player Selected player.
         */
        virtual void setCurrentPlayer(int player)
        {
            this->currentPlayer = player;
            arbiter->setCurrentPlayer(player);
        }
};


#endif // GAME_H
