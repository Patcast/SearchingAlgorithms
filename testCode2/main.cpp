#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include "player.h"
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QGraphicsScene * scene = new QGraphicsScene();
    scene->setSceneRect(0,0,500,600);
    Player * pl = new Player();
    pl->setPixmap(QPixmap(":/images/mario03.png"));
    pl->setFlag(QGraphicsItem::ItemIsFocusable);
    pl->setFocus();

    scene->addItem(pl);
    QGraphicsView * view = new QGraphicsView(scene);
    // show the view
    view->show();




    return a.exec();
}
