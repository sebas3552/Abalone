#include "choosecolor.h"
#include "ui_choosecolor.h"

ChooseColor::ChooseColor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseColor), selectedColors(0)
{
    ui->setupUi(this);
    color = new Colors();
    color->setVisible(false);
    connect(color, SIGNAL(backC()),this, SLOT(hide()));
    connect(color, SIGNAL(colorSelected(int,Color)), this, SLOT(colorChosen(int,Color)));
    connect(color, SIGNAL(helpRequest()), this, SLOT(helpRequested()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));
    //Hide '?' button on window
    Qt::WindowFlags flags = windowFlags();
    this->setWindowFlags(flags & ~Qt::WindowContextHelpButtonHint);
    this->ui->pushButton_4->hide();
}

ChooseColor::~ChooseColor()
{
    delete ui;
    //delete color;
}

void ChooseColor::hide(){
    this->setVisible(true);
    color->setVisible(false);
    if(this->selectedColors == 2)
        this->ui->pushButton_4->show();
}

void ChooseColor::helpRequested()
{
    emit this->helpRequest();
}

void ChooseColor::on_pushButton_clicked()
{
    exit(0);
}

void ChooseColor::on_pushButton_2_clicked()
{
    this->setVisible(false);
    color->setPlayerId(0);
    color->setVisible(true);
    ui->pushButton_2->close();
}


void ChooseColor::on_pushButton_3_clicked()
{
    this->setVisible(false);
    color->setPlayerId(1);
    color->setVisible(true);
    ui->pushButton_3->close();
}

void ChooseColor::colorChosen(int player, Color color)
{
    ++this->selectedColors;
    emit setColor(player, color);
}

void ChooseColor::on_pushButton_4_clicked()
{
    emit startGame();
}

void ChooseColor::on_pushButton_5_clicked()
{
    emit this->helpRequest();
}
