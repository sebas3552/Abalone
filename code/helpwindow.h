#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>

namespace Ui {
class HelpWindow;
}

/**
 * @brief The HelpWindow class shows the game rules or help in a graphical UI window.
 */
class HelpWindow : public QDialog
{
    Q_OBJECT

    public:

        /**
         * @brief Constructs the object.
         * @param parent Pointer to the parent window.
         * @param text Text to be displayed on window.
         */
        HelpWindow(QWidget *parent = nullptr, QString text = "");

        /**
         * @brief Destroys the object.
         */
        ~HelpWindow();

    private slots:

        ///Slot that defines the actions when user presses the save button.
        void on_pushButton_clicked();

    private:

        ///Graphical object.
        Ui::HelpWindow *ui;

        ///Pointer to a QLabel object containing the game rules or help.
        QLabel* rules;
};

#endif // HELPWINDOW_H
