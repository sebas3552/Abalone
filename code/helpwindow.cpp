#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent, QString text) :
    QDialog(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    //Hide '?' button on window
    // create horizontal layout
    QVBoxLayout* layout = new QVBoxLayout();
    // and add label to it
    // set layout to widget
    Qt::WindowFlags flags = windowFlags();
    this->setWindowFlags(flags & ~Qt::WindowContextHelpButtonHint);
    rules = new QLabel(text, this);
    rules->setAlignment(Qt::AlignCenter);
    layout->addWidget(rules);
    layout->addWidget(ui->pushButton);
    this->setLayout(layout);
    ui->label->show();
    this->setWindowTitle("Help");
}

HelpWindow::~HelpWindow()
{
    delete ui;
    delete rules;
}

void HelpWindow::on_pushButton_clicked()
{
    this->setVisible(false);
}
