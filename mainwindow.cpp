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
    QGraphicsScene * scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QGraphicsPixmapItem * world = new QGraphicsPixmapItem();
    world->setPixmap(QPixmap(":/images/worldmap.png").scaled(1500,1500));
    world->setZValue(0.5);
    scene->addItem(world);
    gameWord_ptr = GameWorld::Instance(":/images/worldmap.png",20,60,100.0);
    player.place(gameWord_ptr->protagonist->getXPos()*50,gameWord_ptr->protagonist->getYPos()*50);
    scene->addItem(&player);
    //std::cout<<gameWord_ptr->protagonist->getXPos()<<gameWord_ptr->protagonist->getYPos() << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zoomIn()
  {
  ui->graphicsView->scale(1.2, 1.2);
  }

void MainWindow::zoomOut()
  {
  ui->graphicsView->scale(0.8, 0.8);
  }

