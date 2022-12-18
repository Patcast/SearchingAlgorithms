#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <QProgressBar>
#include <QSpinBox>
#include <iostream>
#include <QLCDNumber>
#include "gameworld.h"
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //GraphicsScene * scene = new GraphicsScene();
    ui->setupUi(this);
    //ui->graphicsView->setScene(scene);
    ui->lineEdit->installEventFilter(this);
    ChangeHealth(GameWorld::Instance()->protagonist->getHealth());
    ChangeEnergy(GameWorld::Instance()->protagonist->getEnergy());
    ui->lcdNumber->display(GameWorld::Instance()->protagonist->getHealth());
    ui->textBrowser->setGeometry(QRect(0, 0, 1, 1));
    //showWin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSignalsFromProtagnist()
{
    connect(GameWorld::Instance()->getProtagonist(),SIGNAL(energyChanged(int)),this,SLOT(ChangeEnergy(int)));
    connect(GameWorld::Instance()->getProtagonist(),SIGNAL(healthChanged(int)),this,SLOT(ChangeHealth(int)));
    connect(GameWorld::Instance()->getProtagonist(),SIGNAL(healthChanged(int)),this,SLOT(ChangeHealthNumber(int)));
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

void MainWindow::ChangeHealthNumber(int x)
{
    ui->lcdNumber->display(x);
}

void MainWindow::showWin()
{
    ui->textBrowser->setText("You win");
    ui->textBrowser->setGeometry(QRect(400, 150, 500, 500));
    ui->textBrowser->setStyleSheet("font-size: 100pt;");
}

void MainWindow::showLoss()
{
    ui->textBrowser->setText("You lose");
    ui->textBrowser->setGeometry(QRect(400, 150, 500, 500));
    ui->textBrowser->setStyleSheet("font-size: 100pt;");
}



bool MainWindow::eventFilter(QObject* obj, QEvent *event)
{
    if (obj == ui->lineEdit)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Up)
            {
                 emit arrowPress(up);
                 return true;
            }
            else if(keyEvent->key() == Qt::Key_Down)
            {
                emit arrowPress(down);
                return true;
            }
            else if(keyEvent->key() == Qt::Key_Left)
            {
                emit arrowPress(left);
                return true;
            }
            else if(keyEvent->key() == Qt::Key_Right)
            {
                emit arrowPress(right);
                return true;
            }
        }
        return false;
    }
    return QMainWindow::eventFilter(obj, event);
}



