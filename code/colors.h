#ifndef COLORS_H
#define COLORS_H

#include <QDialog>
#include <utility>

#include "abalone.h"

///There are six colors available for the pieces.
#define COLORS 6

namespace Ui {
class Colors;
}

/**
 * @brief The Colors class defines an UI window that shows the available colors to the players.
 * From QDialog.
 */
class Colors : public QDialog
{
    Q_OBJECT

    public:

        /**
         * @brief Constructs the object.
         * @param parent Pointer to the parent window.
         */
        explicit Colors(QWidget *parent = nullptr);

        /**
          * @brief Destroys the object.
          */
        ~Colors();

        /**
         * @brief Sets the choosing player id.
         * @param id Id set to the choosing player.
         */
        void setPlayerId(int id);

    signals:

       void backC();

       ///Signal emmited when a player selects a color.
       void colorSelected(int, Color);

       ///Signal emmited to the controller when a player presses the help button.
       void helpRequest();

    private slots:

       ///Slots defining the buttons' actions when pressed.
       void on_pushButton_clicked();
       void on_pushButton_3_clicked();
       void on_pushButton_2_clicked();
       void on_pushButton_4_clicked();
       void on_pushButton_5_clicked();
       void on_pushButton_6_clicked();
       void on_help_clicked();

    private:

        ///Graphical object.
        Ui::Colors *ui;

        ///Id of the current choosing player.
        int playerId;
};

#endif // COLORS_H
