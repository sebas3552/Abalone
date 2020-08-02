#include "gameover.h"
#include "ui_gameover.h"
#include "gamewindow.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);  
}

void GameOver::setWindowInfo(int loser, int winner, Qt::GlobalColor loserColor, Qt::GlobalColor winnerColor)
{
    ui->loser->setText(QString("Player %1 has lost the game!").arg(loser+1));
    ui->winner->setText(QString("Player %1 has won the game!").arg(winner+1));
    GameWindow::setColor(ui->loserButton, loserColor, false);
    GameWindow::setColor(ui->winnerButton, winnerColor, false);
}

GameOver::~GameOver()
{
    //SEGMENTATION FAULT
    //delete ui;
}

void GameOver::on_pushButton_clicked()
{
    emit this->finishGame();
}
