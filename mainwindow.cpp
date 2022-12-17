#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <QProgressBar>
#include <QSpinBox>
#include <iostream>
#include "gameworld.h"

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

void MainWindow::setSignalsFromProtagnist()
{
    connect(GameWorld::Instance()->getProtagonist(),SIGNAL(energyChanged(int)),this,SLOT(ChangeEnergy(int)));
    connect(GameWorld::Instance()->getProtagonist(),SIGNAL(healthChanged(int)),this,SLOT(ChangeHealth(int)));
}

void MainWindow::ChangeHealth(int health)
{


    std::cout<<"HEALTH CHENGE"<<health<<std::endl;
    ui->HealthBar->setRange(0,100);
    ui->HealthBar->setValue(health);
}

void MainWindow::ChangeEnergy(int energy)
{
    std::cout<<"ENERGY CHENGE"<<energy<<std::endl;
    ui->EnergyBar->setRange(0,100);
    ui->EnergyBar->setValue(energy);
}

void MainWindow::heuristicsValue()
{
    heuristics = ui->HeuristicsInput->value();
    //std::cout<<heuristics<< std::endl;
}


