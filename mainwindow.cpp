#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ZoomIn()
  {
  //ui->graphicsView->scale(1.1, 1.1);
    std::cout<<"ZoomIn"<<std::endl;
  }

void MainWindow::ZoomOut()
  {
  //ui->graphicsView->scale(1.1, 1.1);
    std::cout<<"ZoomOut"<<std::endl;
  }
