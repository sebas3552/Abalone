#ifndef CHOOSECOLOR_H
#define CHOOSECOLOR_H

#include <QDialog>

#include "colors.h"

namespace Ui {
class ChooseColor;
}

/**
 * @brief The ChooseColor class modelates an UI window to prompt the players to select their pieces' colors.
 * Inherits from QDialog.
 */
class ChooseColor : public QDialog
{
    Q_OBJECT

    public:

        /**
         * @brief Constructs the object.
         * @param parent Pointer to the parent window.
         */
        explicit ChooseColor(QWidget *parent = nullptr);

        /**
          * @brief Destroys the object.
          */
        ~ChooseColor();

    signals:

        ///Signal emmited to return to another window after the colors were chosen.
        void back();

        ///Signal emmited to the controller to communicate the chosen colors to the game.
        void setColor(int, Color);

        ///Signal emmited when a player presses the play button.
        void startGame(int initialPlayer = 0);

        ///Signal emmited to the controller when the user presses the help button, whether on this window or in Colow window.
        void helpRequest();

    private slots:

        ///Slots defining the buttons' actions when pressed.
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_pushButton_3_clicked();
        void on_pushButton_4_clicked();
        void on_pushButton_5_clicked();

        ///Slot to receive the signal sended by Color window containing the information of the players' selection.
        void colorChosen(int, Color);

        ///Hides this window.
        void hide();

        ///Slot to receive the helpRequest signal from Color window.
        void helpRequested();

private:
        ///Graphical object.
        Ui::ChooseColor *ui;

        ///Pointer to a Color window.
        Colors * color;

        ///Number of colors selected by players.
        int selectedColors;
};

#endif // CHOOSECOLOR_H
