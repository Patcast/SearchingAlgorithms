#include "graphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <iostream>


GraphicsScene::GraphicsScene() : Scene("2d")
{
//    graphScene = new QGraphicsScene();
//    QGraphicsPixmapItem *world = new QGraphicsPixmapItem();
//    world->setPixmap(QPixmap(":/images/worldmap.png").scaled(1500, 1500));
//    world->setZValue(0.5);
//    graphScene->addItem(world);
//    gameWord_ptr = GameWorld::Instance(":/images/worldmap.png", 60, 20, 100.0);
//    player_ptr = new ProtagonistView();
//    player_ptr->place(gameWord_ptr->protagonist->getXPos() * 50, gameWord_ptr->protagonist->getYPos() * 50);
//    graphScene->addItem(player_ptr);
//    // std::cout<<gameWord_ptr->protagonist->getXPos()<<gameWord_ptr->protagonist->getYPos() << std::endl;

//    for(std::unique_ptr<Enemy> &t:gameWord_ptr->enemies){
//        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
//        e->setPixmap(QPixmap(":/images/Goomba.png").scaled(50,50));
//        e->setPos(t->getXPos()*50,t->getYPos()*50);
//        e->setZValue(0.8);
//        graphScene->addItem(e);
//    }

//    for(std::unique_ptr<Tile> &t:gameWord_ptr->healthPacks){
//        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
//        e->setPixmap(QPixmap(":/images/HealthPack.jpg").scaled(50,50));
//        e->setPos(t->getXPos()*50,t->getYPos()*50);
//        e->setZValue(0.8);
//        graphScene->addItem(e);
//        std::cout<<t->getXPos()<< std::endl;
//    }

///*    for(std::optional<std::unique_ptr<Tile>> &t:gameWord_ptr->specialFigures){
//        if(t.has_value()){
//            if(static_cast<Enemy>(*t.value()) == *t.value()){
//                QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
//                e->setPixmap(QPixmap(":/images/HealthPack.jpg").scaled(50,50));
//                e->setPos(t.value()->getXPos()*50,t.value()->getYPos()*50);
//                e->setZValue(0.8);
//                graphScene->addItem(e);

//            }
//            else{
//                QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
//                e->setPixmap(QPixmap(":/images/Goomba.png").scaled(50,50));
//                e->setPos(t.value()->getXPos()*50,t.value()->getYPos()*50);
//                e->setZValue(0.8);
//                graphScene->addItem(e);
//            }
//        }
//    }

//*/
//    QGraphicsView *view = new QGraphicsView(graphScene);
//    this->widget = view;
}

void GraphicsScene::drawEnemy() {
//    for(std::unique_ptr<Enemy> &t:gameWord_ptr->enemies){
//        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
//        e->setPixmap(QPixmap(":/images/Goomba.png").scaled(50,50));
//        e->setPos(t->getXPos()*50,t->getYPos()*50);
//        e->setZValue(0.8);
//        graphScene->addItem(e);
//    }
}
void GraphicsScene::drawDeathEnemy(Enemy en){
    QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
    e->setPixmap(QPixmap(":/images/deadGoomba.png").scaled(50,50));
    e->setPos(en.getXPos()*50,en.getYPos()*50);
    e->setZValue(0.9);
    graphScene->addItem(e);
}

void GraphicsScene::drawProtagonist(){
    player_ptr = new ProtagonistView();
    player_ptr->place(gameWord_ptr->getProtagonist()->getXPos() * 50, gameWord_ptr->getProtagonist()->getYPos() * 50);
    graphScene->addItem(player_ptr);
}
void GraphicsScene::drawTile(){

}
void GraphicsScene::drawHealthPack(){
//    for(std::unique_ptr<Tile> &t:gameWord_ptr->healthPacks){
//        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
//        e->setPixmap(QPixmap(":/images/HealthPack.jpg").scaled(50,50));
//        e->setPos(t->getXPos()*50,t->getYPos()*50);
//        e->setZValue(0.8);
//        graphScene->addItem(e);
//        std::cout<<t->getXPos()<< std::endl;
//    }

}
void GraphicsScene::drawMovement(){

}
void GraphicsScene::zoomIn(){
    QGraphicsView* viewWidget = static_cast<QGraphicsView*>(this->widget);
    viewWidget->scale(1.2, 1.2);
}
void GraphicsScene::zoomOut(){
    QGraphicsView* viewWidget = static_cast<QGraphicsView*>(this->widget);
    viewWidget->scale(0.8, 0.8);
}
