#ifndef ABALONE_H
#define ABALONE_H

#include <iostream>
#include <QObject>
#include <QPair>
#include <QtDebug>

#include "abaloneloader.h"
#include "game.h"
#include "gameloader.h"
#include "piece.h"
#include "player.h"

using namespace std;

/**
 * @brief The Abalone class is used to represent the Abalone game.
 * Inherits from abstract Game and from QObject so that it is able to use the Qt signal-slot mechanism.
 */

class Abalone : public QObject, public Game
{
    Q_OBJECT

    ///Friend declarations to allow saver and controller access the Abalone members.
    friend class AbaloneSaver;
    friend class Controller;

    private:

        /**
         * @brief Initializes all requirements needed before starting the game.
         */
        virtual void init();

        /**
         * @brief Is in charge of termination tasks upon game termination.
         */
        virtual void finalize();

        /**
         * @brief Does the necessary things when a player has won the game.
         */
        virtual int won();

        /**
         * @brief Does the necessary things when a player has lost the game.
         */
        virtual int gameOver();

    protected:
        ///A player is represented by a pair consisting of an id and the color he has selected.
        Player player1;
        Player player2;

    public:

        /**
         * @brief Abalone constructor.
         * @param parent Pointer to the parent object.
         */
        Abalone(QObject* parent = nullptr);

        /**
         * @brief Destroys.
         */
        virtual ~Abalone();

        /**
         * @brief Allow a player to select a color for his pieces.
         * @param player Player id
         * @param color Color selected by the player.
         */
        virtual void chooseColor(int player, Color color) override;

        /**
         * @brief Shows the game rules.
         * @return String containing the game rules.
         */
        virtual QString showRules();

        /**
         * @brief Starts the game.
         * @param initialPlayer Player that starts the game, by default, player 0.
         */
        virtual void play(int initialPlayer = 0);

        /**
         * @brief Loads a previous state of the game from a file.
         * @param filename Name of the file containing the previous state.
         * @return Pointer to a Game object constructed from the information saved in the file.
         */
        virtual Game * load(QString filename);

        /**
         * @brief A game represents itself in a collection of saveable objects.
         * @param objects Collection of saveable objects that conform a game.
         */
        virtual void represent(vector<Saveable *> &objects) override;

        /**
         * @brief Returns the pieces color of the selected player.
         * @param player Player whose pieces color wants to be known.
         * @return the pieces color of the selected player.
         */
        virtual Color getColor(int player);

        /**
         * @brief Returns whose turn it is, in the game play.
         * @return The id of the current player.
         */
        virtual int getCurrentPlayer() const override;

        /**
         * @brief Sets the initial state of the game.
         */
        void initialState();

        ///Used to count the number of buttons clicked, in the test function.
        int clicks = 0;

    signals:
        ///Signal emitted to request the controller to ask the colors to the player.
        void requestColors();

};

#endif // ABALONE_H
