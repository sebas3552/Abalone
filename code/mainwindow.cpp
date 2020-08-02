#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    //escondemos esta ventana y mostramos la ventana de escoger ficha
    this->setVisible(false);
    emit playRequest();
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << "Opening file";
    QString file = QFileDialog::getOpenFileName(this, "Open a file", "C://", "Abalone game (*.aba)");
    if(file.isNull()){
        QMessageBox(QMessageBox::Icon::Critical, "Error", "Error! No file selected!", QMessageBox::Ok, this).exec();
        return;
    }else{
        emit loadRequest(file);
    }
}

void MainWindow::on_pushButton_clicked()
{
    emit helpRequest();
}

