#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QApplication>
#include <QObject>
#include <QString>

#include "abalone.h"
#include "choosecolor.h"
#include "gameover.h"
#include "gamewindow.h"
#include "helpwindow.h"
#include "mainwindow.h"

/**
 * @brief The Controller class defines the controller object in a MVC design pattern.
 * Inherits from QObject to use the Qt signal-slot mechanism.
 * Manages all the graphical windows and the game itself by communicating the user actions from the windows to
 * the game and viceversa.
 */
class Controller : public QObject
{
    Q_OBJECT

    public:

        /**
         * @brief Constructs the object.
         * @param argc Command-line argument.
         * @param argv Command-line argument.
         * @param parent Pointer to the parent object.
         */
        Controller(QApplication* app, MainWindow* mw, Game* game, HelpWindow* helpWindow, ChooseColor* colorWindow, GameWindow* gameWindow, GameOver* gameOver, Saver* saver, QObject* parent = nullptr);

        /**
          * @brief Destroys the object.
          */
        ~Controller();

        /**
         * @brief Is the program entry point.
         * @param argc Command-line argument.
         * @param argv Command-line argument.
         * @return Status upon program completion.
         */
        int main();

    private:

        ///Pointer to the game object.
        Game* game;

        ///Program main window.
        MainWindow* w;

        ///Application for Qt purposes.
        QApplication* a;

        ///Window that displays the game help and rules upon user request.
        HelpWindow* helpWindow;

        ///Window to prompt the players to select their pieces' color.
        ChooseColor* colorWindow;

        ///Window that holds the graphical representation of the game.
        GameWindow* gameWindow;

        ///Pointer to a saver object.
        Saver* saver;

        ///Window that shows a message containing the winner and loser players.
        GameOver* gameOver;

    public slots:

        ///Slot that defines the actions when user presses the play button.
        void playRequested();

        ///Slot that defines the actions when user presses the help button.
        void helpRequested();

        ///Slot that defines the actions when the game object requests the players to select colors.
        void colorsRequested();

        ///Slot that defines the actions when user presses the save button.
        void saveRequested(QString);

        ///Slot to receive the players' color selection from the colors window.
        void setColor(int, Color);

        ///Slot that defines the actions when user presses the load button.
        void loadGameRequested(QString filename);

        ///Slot that defines the actions when user presses the continue button.
        void startGameRequested(int initialPlayer);

        ///Slot that asks the pieces colors to the game, to color the pieces in the interface.
        void askGameColors(int player);

        ///Slot that receives the pieces selected by the players in the interface.
        void selected(QPoint p);

        ///Slot that is triggered when the game has to be finished.
        void finishGameRequested();

    signals:

        ///Signal that sends the pieces color of a selected player.
        void respondColor(Color, int);

        ///Signal sended to the interface to update the current state of the game in the interface.
        void updateUI(vector<vector<Piece*>>, vector<Piece*>, int, vector<QPoint>);
};

#endif // CONTROLLER_H
