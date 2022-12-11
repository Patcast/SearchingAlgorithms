#include "graphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>


GraphicsScene::GraphicsScene() : Scene("2d")
{
    QGraphicsScene *graphScene = new QGraphicsScene();

    QGraphicsPixmapItem *world = new QGraphicsPixmapItem();
    world->setPixmap(QPixmap(":/images/worldmap.png").scaled(1500, 1500));
    world->setZValue(0.5);
    graphScene->addItem(world);
    gameWord_ptr = GameWorld::Instance(":/images/worldmap.png", 20, 60, 100.0);
    player_ptr = new ProtagonistView();
    player_ptr->place(gameWord_ptr->protagonist->getXPos() * 50, gameWord_ptr->protagonist->getYPos() * 50);
    graphScene->addItem(player_ptr);
    // std::cout<<gameWord_ptr->protagonist->getXPos()<<gameWord_ptr->protagonist->getYPos() << std::endl;

    QGraphicsView *view = new QGraphicsView(graphScene);
    this->widget = view;
    
}

void GraphicsScene::drawEnemy() {

}
void GraphicsScene::drawProtagonist(){

}
void GraphicsScene::drawTile(){

}
void GraphicsScene::drawHealthPack(){

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
