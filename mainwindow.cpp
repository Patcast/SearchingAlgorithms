#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <QProgressBar>
#include <QSpinBox>
#include <iostream>
#include "graphicsscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //GraphicsScene * scene = new GraphicsScene();
    ui->setupUi(this);
    //ui->graphicsView->setScene(scene);

    ChangeHealth(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

<<<<<<< Updated upstream
void MainWindow::ZoomIn()
  {
  //ui->graphicsView->scale(1.1, 1.1);
    std::cout<<"ZoomIn"<<std::endl;
  }

void MainWindow::ZoomOut()
  {
  //ui->graphicsView->scale(1.1, 1.1);
    std::cout<<"ZoomOut"<<std::endl;
=======
void MainWindow::setSignalsFromProtagnist()
{
    connect(GameWorld::Instance()->getProtagonist(),SIGNAL(energyChanged(int)),this,SLOT(ChangeEnergy(int)));
    connect(GameWorld::Instance()->getProtagonist(),SIGNAL(healthChanged(int)),this,SLOT(ChangeHealth(int)));
    //connect(GameWorld::Instance()->getProtagonist(),SIGNAL(healthChanged(int)),this,SLOT(newPos(int)));
>>>>>>> Stashed changes
}

void MainWindow::ChangeHealth(int health)
{
<<<<<<< Updated upstream
=======
    std::cout<<"HEALTH CHaNGE"<<health<<std::endl;
>>>>>>> Stashed changes
    ui->HealthBar->setRange(0,100);
    ui->HealthBar->setValue(health);
}

void MainWindow::ChangeEnergy(int energy)
{
    ui->EnergyBar->setRange(0,100);
    ui->EnergyBar->setValue(energy);
}

void MainWindow::heuristicsValue()
{
    heuristics = ui->HeuristicsInput->value();
    //std::cout<<heuristics<< std::endl;
}

/*
 * void MainWindow::newPos(int x)
{
 std::cout<< "x<<y"<< std::endl;
}
*/


