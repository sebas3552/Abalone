#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class represents the window at the entry point in the program.
 * Inherits from QMainWindow.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        /**
         * @brief Constructs the object.
         * @param parent Pointer to the parent object.
         */
        explicit MainWindow(QWidget *parent = nullptr);

        /**
          * @brief Destroys the object.
          */
        ~MainWindow();

    signals:

        ///@brief Signal emitted to the controller when the user starts the game.
        void playRequest();

        ///@brief Signal emitted to the controller when the user presses the help button on the UI.
        void helpRequest();

        /**
         * @brief Signal emitted when the user wants to save the current game state.
         * @param filename String containing the file name where the game state is to be stored.
         */
        void saveRequest(QString filename);

        /**
         * @brief Signal emitted when the user wants to load the game from a file.
         * @param file String containing the file name where the game state was saved.
         */
        void loadRequest(QString file);

    private slots:

        ///Slots that define the actions when the users presses a certain button.
        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

        void on_pushButton_4_clicked();

    private:

        ///Pointer to graphical object.
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
