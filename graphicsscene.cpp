#include "graphicsscene.h"
#include "specialmap.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <iostream>


GraphicsScene::GraphicsScene() : Scene("2d")
{
    QGraphicsScene graphScene = new QGraphicsScene();
    QGraphicsPixmapItem *world = new QGraphicsPixmapItem();
    world->setPixmap(QPixmap(":/images/worldmap.png").scaled(1500, 1500));
    world->setZValue(0.5);
    graphScene.addItem(world);
    gameWord_ptr = GameWorld::Instance(":/images/worldmap.png", 60, 20, 100.0);
    player_ptr = new ProtagonistView();
    player_ptr->place(gameWord_ptr->getProtagonist()->getXPos(), gameWord_ptr->getProtagonist()->getYPos(),50);
    graphScene.addItem(player_ptr);
    // std::cout<<gameWord_ptr->protagonist->getXPos()<<gameWord_ptr->protagonist->getYPos() << std::endl;

    for(std::unique_ptr<Enemy> &t:gameWord_ptr->getSpecialFiguresVector()){
        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
        e->setPixmap(QPixmap(":/images/Goomba.png").scaled(50,50));
        e->setPos(t->getXPos()*50,t->getYPos()*50);
        e->setZValue(0.8);
        graphScene.addItem(e);
    }

    for(std::unique_ptr<Tile> &t:gameWord_ptr->healthPacks){
        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
        e->setPixmap(QPixmap(":/images/HealthPack.jpg").scaled(50,50));
        e->setPos(t->getXPos()*50,t->getYPos()*50);
        e->setZValue(0.8);
        graphScene->addItem(e);
        std::cout<<t->getXPos()<< std::endl;
    }

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
    QGraphicsView *view = new QGraphicsView(graphScene);
    this->widget = view;
}

void GraphicsScene::drawDeathEnemy(Enemy en){
    QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
    e->setPixmap(QPixmap(":/images/deadGoomba.png").scaled(stepsize,stepsize));
    e->setPos(en.getXPos()*stepsize,en.getYPos()*stepsize);
    e->setZValue(0.9);
    graphScene->addItem(e);
}

void GraphicsScene::drawProtagonist(){
    player_ptr = new ProtagonistView();
//    player_ptr->place(gameWord_ptr->getProtagonist()->getXPos() * 50, gameWord_ptr->getProtagonist()->getYPos() * 50);
    graphScene->addItem(player_ptr);
}
void GraphicsScene::drawTile(){
//    for(std::unique_ptr<Tile> &t:gameWord_ptr->tiles){
//        specialMap * e = new specialMap(t->getXPos()*50,t->getYPos()*50,t->getValue());
//        graphScene->addItem(e);
//    }

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
    // if right
    for(int y = ypos-rangeAroundPro; y<ypos+rangeAroundPro;y++ ){
        if(y >=0 && y <= rows && xpos + rangeAroundPro < columns){
//            specialMap * e = new specialMap(xpos+rangeAroundPro,y,gameWord_ptr->tiles.at(xpos+rangeAroundPro+y*columns)->getValue());
//            graphScene->addItem(e);
        }
    }

    // if left
    for(int y = ypos-rangeAroundPro; y<ypos+rangeAroundPro;y++ ){
        if(y >=0 && y <= rows && xpos +rangeAroundPro < columns){
//            specialMap * e = new specialMap(xpos-rangeAroundPro,y,gameWord_ptr->tiles.at(xpos-rangeAroundPro+y*columns)->getValue());
//            graphScene->addItem(e);
        }
    }
    // if up
    for(int x = xpos-rangeAroundPro; x<ypos+rangeAroundPro;x++ ){
        if(x >=0 && x <= columns && ypos-rangeAroundPro > 0){
//            specialMap * e = new specialMap(x,ypos-rangeAroundPro,gameWord_ptr->tiles.at(x+ypos-rangeAroundPro*columns)->getValue());
//            graphScene->addItem(e);
        }
    }
    // if down
    for(int x = xpos-rangeAroundPro; x<ypos+rangeAroundPro;x++ ){
        if(x >=0 && x <= columns && ypos-rangeAroundPro > 0){
//            specialMap * e = new specialMap(x,ypos+rangeAroundPro,gameWord_ptr->tiles.at(x+ypos-rangeAroundPro*columns)->getValue());
//            graphScene->addItem(e);
        }
    }
}
void GraphicsScene::zoomIn(){
    QGraphicsView* viewWidget = static_cast<QGraphicsView*>(this->widget);
    viewWidget->scale(1.2, 1.2);
}
void GraphicsScene::zoomOut(){
    QGraphicsView* viewWidget = static_cast<QGraphicsView*>(this->widget);
    viewWidget->scale(0.8, 0.8);
}

void GraphicsScene::drawEnemy(){
    int i = 0;
    for(int x = 0; x<columns; x++){
        for(int y = 0; y<rows; y++){
            if(gameWord_ptr->getNodes()[x+columns]->getSpecialFigure_ptr().get() != nullptr){
                if(Enemy enemyReference = dynamic_cast<Enemy>(gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr().get())){
                    enemyView e = new enemyView();
                    e->place(gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getXPos(),gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getYPos(),stepsize);
                    showValue(gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getXPos(),gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getYPos(),gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getValue());
                    graphScene->addItem(e);
                    i++;
                    }
                else{
                    healthPackView e = new healthPackView();
                    e->place(gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getXPos(),gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getYPos(),stepsize);
                    showValue(gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getXPos(),gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getYPos(),gameWord_ptr->nodes[x+ycolumns]->getSpecialFigure_ptr()->getValue());
                    graphScene->addItem(e);
                    }
                }
            }
        }
    std::cout<<i<< std::endl;
}
