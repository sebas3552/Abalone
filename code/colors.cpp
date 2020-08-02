#include <iostream>
#include <QPalette>
#include <QColorDialog>

#include "colors.h"
#include "ui_colors.h"

using namespace std;

Colors::Colors(QWidget *parent)
: QDialog(parent), ui(new Ui::Colors), playerId(-1)
{
    ui->setupUi(this);

    //Sets the color for each button manually.
    QColor buttonColors[6];
    buttonColors[0] = QColor(Qt::GlobalColor::red);
    buttonColors[1] = QColor(Qt::GlobalColor::cyan);
    buttonColors[2] = QColor(Qt::GlobalColor::blue);
    buttonColors[3] = QColor(Qt::GlobalColor::white);
    buttonColors[4] = QColor(Qt::GlobalColor::yellow);
    buttonColors[5] = QColor(Qt::GlobalColor::green);

    QPushButton** buttons = new QPushButton*[6];
    buttons[0] = ui->pushButton;
    buttons[1] = ui->pushButton_2;
    buttons[2] = ui->pushButton_3;
    buttons[3] = ui->pushButton_4;
    buttons[4] = ui->pushButton_5;
    buttons[5] = ui->pushButton_6;

    for(int button = 0; button < COLORS; ++button){
        QString qss = QString("background-color: %1").arg(buttonColors[button].name()); //sets the background color for each button
        buttons[button]->setStyleSheet(qss);
    }

    //Hide '?' button on window
    Qt::WindowFlags flags = windowFlags();
    this->setWindowFlags(flags & ~Qt::WindowContextHelpButtonHint);

    this->setWindowTitle("Pick a color");
}

Colors::~Colors()
{
    delete ui;
}
void Colors::setPlayerId(int id){
   playerId = id;
}

void Colors::on_pushButton_clicked()
{
    ui->pushButton->close();
    /*Notifies the chooseColor window the color selected by the player, which in turn notifies the controller
    the same information, which finally sets the color and player in the game.*/
    emit colorSelected(playerId, Color::red);
    emit(backC());
}

void Colors::on_pushButton_2_clicked()
{
   ui->pushButton_2->close();
   emit colorSelected(playerId, Color::cyan);
   emit(backC());
}

void Colors::on_pushButton_3_clicked()
{
    ui->pushButton_3->close();
    emit colorSelected(playerId, Color::blue);
    emit(backC());
}

void Colors::on_pushButton_4_clicked()
{
    ui->pushButton_4->close();
    emit colorSelected(playerId, Color::white);
    emit(backC());
}

void Colors::on_pushButton_5_clicked()
{
    ui->pushButton_5->close();
    emit colorSelected(playerId, Color::yellow);
    emit(backC());
}



void Colors::on_pushButton_6_clicked()
{
    ui->pushButton_6->close();
    emit colorSelected(playerId, Color::green);
    emit(backC());
}

void Colors::on_help_clicked()
{
    emit this->helpRequest();
}
