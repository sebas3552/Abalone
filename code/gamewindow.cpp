#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPalette>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow),
    colorPlayer1(Qt::GlobalColor::gray),
    colorPlayer2(Qt::GlobalColor::gray)
{
    ui->setupUi(this);
    connect(ui->help, SIGNAL(clicked(bool)), this, SLOT(on_help_clicked()));
    this->init();
}

GameWindow::~GameWindow()
{
    for(int i = 0; i < ROWS; ++i){
        delete [] this->buttons[i];
    }
    delete this->buttons;

    delete this->lostPiecesPlayer1;
    delete this->lostPiecesPlayer2;
    delete ui;
}

void GameWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open a folder", "C://", "Abalone game (*.aba)");
    if(!fileName.isNull())
        emit saveRequest(fileName);
    else
        QMessageBox(QMessageBox::Icon::Critical, "Error", "Game not saved!", QMessageBox::Ok, this).exec();
}


void GameWindow::on_help_clicked()
{
    emit this->helpRequest();
}

void GameWindow::setColor(QPushButton* button, Color color, bool enabled){
    QString qss = QString("QPushButton {\
                          color: #333;\
                          border: 2px solid #555;\
                          border-radius: 20px;\
                          border-style: outset;\
                          background: qradialgradient(\
                              cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,\
                              radius: 1.35, stop: 0 %1, stop: 1 %2\
                              );\
                          padding: 5px;\
                          }\
                      \
                      QPushButton:hover {\
                          background: qradialgradient(\
                              cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,\
                              radius: 1.35, stop: 0 %3, stop: 1 %4\
                              );\
                          }\
                      \
                      QPushButton:pressed {\
                          border-style: inset;\
                          background: qradialgradient(\
                              cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,\
                              radius: 1.35, stop: 0 %5, stop: 1 %6\
                              );\
                          }").arg(QColor(color).name())\
                        .arg(QColor(color).name())\
                        .arg((enabled ? QColor(color).lighter(125).name() : QColor(color).name()))\
                        .arg((enabled ? QColor(color).lighter(175).name() : QColor(color).name()))\
                        .arg((enabled ? QColor(color).darker(150).name() : QColor(color).name()))\
                        .arg((enabled ? QColor(color).darker(225).name() : QColor(color).name()));
    button->setStyleSheet(qss);

}

void GameWindow::init()
{
    this->buttons = new QPushButton**[ROWS]();
    for(int row = 0; row < ROWS; ++row)
        this->buttons[row] = new QPushButton*[COLUMNS]();

    this->buttons[0][4] = ui->pushButton;
    this->buttons[0][5] = ui->pushButton_2;
    this->buttons[0][6] = ui->pushButton_3;
    this->buttons[0][7] = ui->pushButton_4;
    this->buttons[0][8] = ui->pushButton_5;
    this->buttons[1][3] = ui->pushButton_6;
    this->buttons[1][4] = ui->pushButton_7;
    this->buttons[1][5] = ui->pushButton_8;
    this->buttons[1][6] = ui->pushButton_9;
    this->buttons[1][7] = ui->pushButton_10;
    this->buttons[1][8] = ui->pushButton_11;
    this->buttons[2][2] = ui->pushButton_12;
    this->buttons[2][3] = ui->pushButton_13;
    this->buttons[2][4] = ui->pushButton_14;
    this->buttons[2][5] = ui->pushButton_15;
    this->buttons[2][6] = ui->pushButton_16;
    this->buttons[2][7] = ui->pushButton_17;
    this->buttons[2][8] = ui->pushButton_18;
    this->buttons[3][1] = ui->pushButton_19;
    this->buttons[3][2] = ui->pushButton_20;
    this->buttons[3][3] = ui->pushButton_21;
    this->buttons[3][4] = ui->pushButton_22;
    this->buttons[3][5] = ui->pushButton_23;
    this->buttons[3][6] = ui->pushButton_24;
    this->buttons[3][7] = ui->pushButton_25;
    this->buttons[3][8] = ui->pushButton_26;
    this->buttons[4][0] = ui->pushButton_27;
    this->buttons[4][1] = ui->pushButton_28;
    this->buttons[4][2] = ui->pushButton_29;
    this->buttons[4][3] = ui->pushButton_30;
    this->buttons[4][4] = ui->pushButton_31;
    this->buttons[4][5] = ui->pushButton_32;
    this->buttons[4][6] = ui->pushButton_33;
    this->buttons[4][7] = ui->pushButton_34;
    this->buttons[4][8] = ui->pushButton_35;
    this->buttons[5][0] = ui->pushButton_36;
    this->buttons[5][1] = ui->pushButton_37;
    this->buttons[5][2] = ui->pushButton_38;
    this->buttons[5][3] = ui->pushButton_39;
    this->buttons[5][4] = ui->pushButton_40;
    this->buttons[5][5] = ui->pushButton_41;
    this->buttons[5][6] = ui->pushButton_42;
    this->buttons[5][7] = ui->pushButton_43;
    this->buttons[6][0] = ui->pushButton_44;
    this->buttons[6][1] = ui->pushButton_45;
    this->buttons[6][2] = ui->pushButton_46;
    this->buttons[6][3] = ui->pushButton_47;
    this->buttons[6][4] = ui->pushButton_48;
    this->buttons[6][5] = ui->pushButton_49;
    this->buttons[6][6] = ui->pushButton_50;
    this->buttons[7][0] = ui->pushButton_51;
    this->buttons[7][1] = ui->pushButton_52;
    this->buttons[7][2] = ui->pushButton_53;
    this->buttons[7][3] = ui->pushButton_54;
    this->buttons[7][4] = ui->pushButton_55;
    this->buttons[7][5] = ui->pushButton_56;
    this->buttons[8][0] = ui->pushButton_57;
    this->buttons[8][1] = ui->pushButton_58;
    this->buttons[8][2] = ui->pushButton_59;
    this->buttons[8][3] = ui->pushButton_60;
    this->buttons[8][4] = ui->pushButton_61;

    this->lostPiecesPlayer1 = new QPushButton*[MAX_LOST_PIECES];
    this->lostPiecesPlayer2 = new QPushButton*[MAX_LOST_PIECES];

    this->lostPiecesPlayer1[0] = ui->pushButton_62;
    this->lostPiecesPlayer1[1] = ui->pushButton_63;
    this->lostPiecesPlayer1[2] = ui->pushButton_64;
    this->lostPiecesPlayer1[3] = ui->pushButton_65;
    this->lostPiecesPlayer1[4] = ui->pushButton_66;
    this->lostPiecesPlayer1[5] = ui->pushButton_67;

    this->lostPiecesPlayer2[0] = ui->pushButton_68;
    this->lostPiecesPlayer2[1] = ui->pushButton_69;
    this->lostPiecesPlayer2[2] = ui->pushButton_70;
    this->lostPiecesPlayer2[3] = ui->pushButton_71;
    this->lostPiecesPlayer2[4] = ui->pushButton_72;
    this->lostPiecesPlayer2[5] = ui->pushButton_73;

    for(int piece = 0; piece < MAX_LOST_PIECES; ++piece){
        this->lostPiecesPlayer1[piece]->setVisible(false);
        this->lostPiecesPlayer2[piece]->setVisible(false);
        this->lostPiecesPlayer1[piece]->setEnabled(false);
        this->lostPiecesPlayer2[piece]->setEnabled(false);
    }
}

void GameWindow::colorReceived(Color color, int player)
{
    cout << "color chosen for player "<< player << " : " << color << endl;
    if(player == 0)
        this->colorPlayer1 = color;
    else
        this->colorPlayer2 = color;
}

void GameWindow::update(vector<vector<Piece *>> board, vector<Piece *> lostPieces, int currentPlayer, vector<QPoint> canMoveList)
{
    for(int row = 0; row < ROWS; ++row){
        for(int column = 0; column < COLUMNS; ++column){
            if(this->buttons[row][column] && board[row][column]){
                this->setColor(this->buttons[row][column], board[row][column]->getColor());
                if(board[row][column]->getColor() != Color::gray && board[row][column]->getOwner() == currentPlayer)
                    this->buttons[row][column]->setEnabled(true);
                else
                    if(board[row][column]->getColor() != Color::gray && board[row][column]->getOwner() != currentPlayer)
                        this->buttons[row][column]->setEnabled(false);
                else{
                   this->setColor(this->buttons[row][column], Color::gray, false);
                   this->buttons[row][column]->setEnabled(false);
                }

            }else{
                if(this->buttons[row][column]){
                    this->setColor(this->buttons[row][column], Color::gray, false);
                    this->buttons[row][column]->setEnabled(false);
                }
            }
        }
    }
    int firstPlayerPieces = 0;
    int secondPlayerPieces = 0;
    if(!lostPieces.empty()){
        for(size_t lostPiece = 0; lostPiece < lostPieces.size(); ++lostPiece){
            if(lostPieces[lostPiece]->getOwner() == 0){
                this->setColor(this->lostPiecesPlayer1[firstPlayerPieces], lostPieces[lostPiece]->getColor());
                this->lostPiecesPlayer1[firstPlayerPieces]->setVisible(true);
                ++firstPlayerPieces;
            }
            else{
                this->setColor(this->lostPiecesPlayer2[secondPlayerPieces], lostPieces[lostPiece]->getColor());
                this->lostPiecesPlayer2[secondPlayerPieces]->setVisible(true);
                ++secondPlayerPieces;
            }
        }
    }
    for(auto piece : canMoveList){
        this->buttons[piece.y()][piece.x()]->setEnabled(true);
        if(!board[piece.y()][piece.x()])
            this->setColor(this->buttons[piece.y()][piece.x()], Color::gray, true);
    }

    qDebug() << "Current player: " << currentPlayer << " color: " << this->colorPlayer1 << endl;
    if(this->colorPlayer1 == Qt::GlobalColor::gray){
        emit this->requestColor(0);
        emit this->requestColor(1);
    }
    this->setColor(this->ui->currentPlayerButton, (currentPlayer == 0? this->colorPlayer1 : this->colorPlayer2), false);
}

void GameWindow::on_pushButton_clicked()
{
    emit this->select(QPoint(0,4));
}

void GameWindow::on_pushButton_2_clicked()
{
    emit this->select(QPoint(0,5));
}

void GameWindow::on_pushButton_3_clicked()
{
    emit this->select(QPoint(0,6));
}

void GameWindow::on_pushButton_4_clicked()
{
    emit this->select(QPoint(0,7));
}

void GameWindow::on_pushButton_5_clicked()
{
    emit this->select(QPoint(0,8));
}

void GameWindow::on_pushButton_6_clicked()
{
    emit this->select(QPoint(1,3));
}

void GameWindow::on_pushButton_7_clicked()
{
    emit this->select(QPoint(1,4));
}

void GameWindow::on_pushButton_8_clicked()
{
    emit this->select(QPoint(1,5));
}

void GameWindow::on_pushButton_9_clicked()
{
    emit this->select(QPoint(1,6));
}


void GameWindow::on_pushButton_10_clicked()
{
    emit this->select(QPoint(1,7));
}

void GameWindow::on_pushButton_11_clicked()
{
    emit this->select(QPoint(1,8));
}

void GameWindow::on_pushButton_12_clicked()
{
    emit this->select(QPoint(2,2));
}

void GameWindow::on_pushButton_13_clicked()
{
    emit this->select(QPoint(2,3));
}

void GameWindow::on_pushButton_14_clicked()
{
    emit this->select(QPoint(2,4));
}

void GameWindow::on_pushButton_15_clicked()
{
    emit this->select(QPoint(2,5));
}

void GameWindow::on_pushButton_16_clicked()
{
    emit this->select(QPoint(2,6));
}

void GameWindow::on_pushButton_17_clicked()
{
    emit this->select(QPoint(2,7));
}

void GameWindow::on_pushButton_18_clicked()
{
    emit this->select(QPoint(2,8));
}

void GameWindow::on_pushButton_19_clicked()
{
    emit this->select(QPoint(3,1));
}

void GameWindow::on_pushButton_20_clicked()
{
    emit this->select(QPoint(3,2));
}

void GameWindow::on_pushButton_21_clicked()
{
    emit this->select(QPoint(3,3));
}

void GameWindow::on_pushButton_22_clicked()
{
    emit this->select(QPoint(3,4));
}

void GameWindow::on_pushButton_23_clicked()
{
    emit this->select(QPoint(3,5));
}

void GameWindow::on_pushButton_24_clicked()
{
    emit this->select(QPoint(3,6));
}

void GameWindow::on_pushButton_25_clicked()
{
    emit this->select(QPoint(3,7));
}

void GameWindow::on_pushButton_26_clicked()
{
    emit this->select(QPoint(3,8));
}

void GameWindow::on_pushButton_27_clicked()
{
    emit this->select(QPoint(4,0));
}

void GameWindow::on_pushButton_28_clicked()
{
    emit this->select(QPoint(4,1));
}

void GameWindow::on_pushButton_29_clicked()
{
    emit this->select(QPoint(4,2));
}

void GameWindow::on_pushButton_30_clicked()
{
    emit this->select(QPoint(4,3));
}

void GameWindow::on_pushButton_31_clicked()
{
    emit this->select(QPoint(4,4));
}

void GameWindow::on_pushButton_32_clicked()
{
    emit this->select(QPoint(4,5));
}

void GameWindow::on_pushButton_33_clicked()
{
    emit this->select(QPoint(4,6));
}

void GameWindow::on_pushButton_34_clicked()
{
    emit this->select(QPoint(4,7));
}

void GameWindow::on_pushButton_35_clicked()
{
    emit this->select(QPoint(4,8));
}

void GameWindow::on_pushButton_36_clicked()
{
    emit this->select(QPoint(5,0));
}

void GameWindow::on_pushButton_37_clicked()
{
    emit this->select(QPoint(5,1));
}

void GameWindow::on_pushButton_38_clicked()
{
    emit this->select(QPoint(5,2));
}

void GameWindow::on_pushButton_39_clicked()
{
    emit this->select(QPoint(5,3));
}

void GameWindow::on_pushButton_40_clicked()
{
    emit this->select(QPoint(5,4));
}

void GameWindow::on_pushButton_41_clicked()
{
    emit this->select(QPoint(5,5));
}

void GameWindow::on_pushButton_42_clicked()
{
    emit this->select(QPoint(5,6));
}

void GameWindow::on_pushButton_43_clicked()
{
    emit this->select(QPoint(5,7));
}

void GameWindow::on_pushButton_44_clicked()
{
    emit this->select(QPoint(6,0));
}

void GameWindow::on_pushButton_45_clicked()
{
    emit this->select(QPoint(6,1));
}

void GameWindow::on_pushButton_46_clicked()
{
    emit this->select(QPoint(6,2));
}

void GameWindow::on_pushButton_47_clicked()
{
    emit this->select(QPoint(6,3));
}

void GameWindow::on_pushButton_48_clicked()
{
    emit this->select(QPoint(6,4));
}

void GameWindow::on_pushButton_49_clicked()
{
    emit this->select(QPoint(6,5));
}

void GameWindow::on_pushButton_50_clicked()
{
    emit this->select(QPoint(6,6));
}

void GameWindow::on_pushButton_51_clicked()
{
    emit this->select(QPoint(7,0));
}

void GameWindow::on_pushButton_52_clicked()
{
    emit this->select(QPoint(7,1));
}

void GameWindow::on_pushButton_53_clicked()
{
    emit this->select(QPoint(7,2));
}

void GameWindow::on_pushButton_54_clicked()
{
    emit this->select(QPoint(7,3));
}

void GameWindow::on_pushButton_55_clicked()
{
    emit this->select(QPoint(7,4));
}

void GameWindow::on_pushButton_56_clicked()
{
    emit this->select(QPoint(7,5));
}

void GameWindow::on_pushButton_57_clicked()
{
    emit this->select(QPoint(8,0));
}

void GameWindow::on_pushButton_58_clicked()
{
    emit this->select(QPoint(8,1));
}

void GameWindow::on_pushButton_59_clicked()
{
    emit this->select(QPoint(8,2));
}

void GameWindow::on_pushButton_60_clicked()
{
    emit this->select(QPoint(8,3));
}

void GameWindow::on_pushButton_61_clicked()
{
    emit this->select(QPoint(8,4));
}
