#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <vector>

#include "piece.h"
#include "board.h"

namespace Ui {
class GameWindow;
}

typedef Qt::GlobalColor Color;

/**
 * @brief The GameWindow class shows the graphical representation of the game.
 * Inherits from QDialog.
 */
class GameWindow : public QDialog
{
    Q_OBJECT

    public:

        /**
         * @brief Constructs the object.
         * @param parent Pointer to the parent window.
         */
        explicit GameWindow(QWidget *parent = 0);

        /**
          * @brief Destroys the object.
          */
        ~GameWindow();

        /**
         * @brief Sets the color of the button passed as argument.
         * @param button Button to set the color.
         * @param color Color to be set to the button.
         * @param enabled Flag to represent if the button is to be enabled or not.
        */
        static void setColor(QPushButton* button, Color color, bool enabled = true);

    private slots:

        ///Slot that defines the actions when user presses the save button.
        void on_save_clicked();

        ///Slot that defines the actions when user presses the help button.
        void on_help_clicked();

        ///Slot that defines the actions when color is requested
        void colorReceived(Color, int);

        ///Slot that defines the actions when update is requested
        void update(vector<vector<Piece*>>, vector<Piece*>, int, vector<QPoint>);

        ///Slots that define the actions when a button representing a piece is pressed.
        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

        void on_pushButton_3_clicked();

        void on_pushButton_4_clicked();

        void on_pushButton_5_clicked();

        void on_pushButton_9_clicked();

        void on_pushButton_7_clicked();

        void on_pushButton_8_clicked();

        void on_pushButton_6_clicked();

        void on_pushButton_10_clicked();

        void on_pushButton_11_clicked();

        void on_pushButton_13_clicked();

        void on_pushButton_14_clicked();

        void on_pushButton_17_clicked();

        void on_pushButton_12_clicked();

        void on_pushButton_15_clicked();

        void on_pushButton_16_clicked();

        void on_pushButton_18_clicked();

        void on_pushButton_19_clicked();

        void on_pushButton_24_clicked();

        void on_pushButton_21_clicked();

        void on_pushButton_22_clicked();

        void on_pushButton_23_clicked();

        void on_pushButton_20_clicked();

        void on_pushButton_25_clicked();

        void on_pushButton_26_clicked();

        void on_pushButton_28_clicked();

        void on_pushButton_30_clicked();

        void on_pushButton_31_clicked();

        void on_pushButton_34_clicked();

        void on_pushButton_29_clicked();

        void on_pushButton_33_clicked();

        void on_pushButton_27_clicked();

        void on_pushButton_32_clicked();

        void on_pushButton_35_clicked();

        void on_pushButton_37_clicked();

        void on_pushButton_39_clicked();

        void on_pushButton_40_clicked();

        void on_pushButton_43_clicked();

        void on_pushButton_38_clicked();

        void on_pushButton_42_clicked();

        void on_pushButton_36_clicked();

        void on_pushButton_41_clicked();

        void on_pushButton_44_clicked();

        void on_pushButton_49_clicked();

        void on_pushButton_46_clicked();

        void on_pushButton_47_clicked();

        void on_pushButton_48_clicked();

        void on_pushButton_45_clicked();

        void on_pushButton_50_clicked();

        void on_pushButton_52_clicked();

        void on_pushButton_53_clicked();

        void on_pushButton_56_clicked();

        void on_pushButton_51_clicked();

        void on_pushButton_54_clicked();

        void on_pushButton_55_clicked();

        void on_pushButton_60_clicked();

        void on_pushButton_58_clicked();

        void on_pushButton_59_clicked();

        void on_pushButton_57_clicked();

        void on_pushButton_61_clicked();

    private:

        ///Graphical object.
        Ui::GameWindow *ui;

        ///Matrix of round buttons representing the game pieces.
        QPushButton*** buttons;

        ///Vector of player1's lost pieces.
        QPushButton** lostPiecesPlayer1;

        ///Vector of player2's lost pieces.
        QPushButton** lostPiecesPlayer2;

        ///Pieces color selected by player 1.
        Color colorPlayer1;

        ///Pieces color selected by player 2.
        Color colorPlayer2;

        const int ROWS = 9;
        const int COLUMNS = 9;
        const int MAX_LOST_PIECES = 6;

        /**
         * @brief Initializes the buttons (pieces) on the graphical board.
        */
        void init();

    signals:

        ///Signal emmited to the controller when the save button is pressed.
        void saveRequest(QString);

        ///Signal emmited to the controller when the help button is pressed.
        void helpRequest();

        ///Signal emmited to the controller when color is requested
        void requestColor(int player);

        ///Signal emmited to the controller when a button is pressed.
        void select(QPoint p);
};

#endif // GAMEWINDOW_H
