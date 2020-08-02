#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QString>

namespace Ui {
class GameOver;
}

class GameOver : public QDialog
{
    Q_OBJECT

    public:

         /**
         * @brief Constructs the object with default parent window.
         * @param parent
         */
        explicit GameOver(QWidget *parent = 0);

        /**
         * @brief Destroys the object.
         */
        ~GameOver();

        /**
         * @brief Sets the window info, such as the winner and looser players, and their pieces' colors.
         */
        void setWindowInfo(int, int, Qt::GlobalColor, Qt::GlobalColor);

    signals:

        ///Signal emmited when the game is over.
        void finishGame();

    private slots:
        ///Slot that defines the action when a button is pressed.
        void on_pushButton_clicked();

    private:

        Ui::GameOver *ui;
};

#endif // GAMEOVER_H
