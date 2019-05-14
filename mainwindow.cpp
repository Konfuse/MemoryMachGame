#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QProgressBar>
#include <QString>
#include <QLabel>
#include <myScence.h>
#include <QDebug>
#include <QTimer>
#include<QKeyEvent>
#include <QTime>
#include <cstdlib>
#include <QDialog>
#include <iostream>
#include <QDebug>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->myGraphicsView->setScene(sc); //myGraphicsView
    this->ui->radioButton->setChecked(true);

    this->grabKeyboard();

   // connect(timer, SIGNAL(timeout()), this, SLOT(update_time()));
 //   timer->start(1000);
   // this->time = new QTimer();
 //   time = new QTime();
   // time->restart();
}

MainWindow::~MainWindow() //析构函数
{
    delete sc;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->sc = new myScence(0,4,6);
    this->sc->typeButton = judge();
    this->sc->mw = this;
    this->ui->myGraphicsView->setScene(sc);
    //在按下push_button 的时候 临时创建一个timer
  //  this->sc->time_credit=0;
  //  time->restart();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->sc = new myScence(0,6,4);
    this->sc->typeButton = judge();
    this->sc->mw = this;
    this->ui->myGraphicsView->setScene(sc);
 //   time->restart();
//    this->sc->time_credit=0;
//    timer->start(1000);

}

void MainWindow::on_pushButton_3_clicked()
{
    this->sc = new myScence(0,8,2);
    this->sc->typeButton = judge();
    this->sc->mw = this;
    this->ui->myGraphicsView->setScene(sc);
  //  time->restart();
 //   this->sc->time_credit=0;
 //   timer->start(1000);

}

int MainWindow::judge(){
    if(this->ui->radioButton->isChecked()) return 1;
    else if(this->ui->radioButton_2->isChecked()) return 2;
    else return 3;
}
/*
void MainWindow::update_time(){
    this->ui->lineEdit->setText(QString::number(this->sc->time_credit));
   // qDebug()<<QString::number(this->time_credit,10);
}
*/
