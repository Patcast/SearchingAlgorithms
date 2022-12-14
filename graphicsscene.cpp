#include "graphicsscene.h"
#include "specialmap.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <iostream>


GraphicsScene::GraphicsScene() : Scene("2d")
{
    graphScene = new QGraphicsScene();
    /*QGraphicsPixmapItem *world = new QGraphicsPixmapItem();
    world->setPixmap(QPixmap(":/images/worldmap.png").scaled(1500, 1500));
    world->setZValue(0.5);
    graphScene->addItem(world);
    */
    gameWord_ptr = GameWorld::Instance(":/images/worldmap.png", 60, 20, 100.0);
    xpos = gameWord_ptr->protagonist->getXPos();
    ypos = gameWord_ptr->protagonist->getYPos();
    rangeAroundPro = 10;

    rows = gameWord_ptr->totalRows;
    columns = gameWord_ptr->totalColumns;



    player_ptr = new ProtagonistView();
    player_ptr->place(gameWord_ptr->protagonist->getXPos(), gameWord_ptr->protagonist->getYPos(),stepsize);
    graphScene->addItem(player_ptr);

    for(int x =xpos-rangeAroundPro; x<xpos+rangeAroundPro;x++ ){
        for(int y =ypos-rangeAroundPro; y<ypos+rangeAroundPro;y++ ){
            if(x >= 0 && x <= columns && y >=0 && y <= rows){
                specialMap * e = new specialMap(x,y,gameWord_ptr->tiles.at(x+y*columns)->getValue());
                graphScene->addItem(e);
            }
        }
    }
/*

            specialMap * e = new specialMap(t->getXPos(),t->getYPos(),t->getValue());
            std::cout<<xpos-t->getXPos()<< " "<<ypos-t->getYPos()<< std::endl;
            graphScene->addItem(e);
*/


    for(std::unique_ptr<Enemy> &t:gameWord_ptr->enemies){
        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
        e->setPixmap(QPixmap(":/images/Goomba.png").scaled(stepsize,stepsize));
        e->setPos(t->getXPos()*stepsize,t->getYPos()*stepsize);
        e->setZValue(0.8);
        graphScene->addItem(e);
    }

    for(std::unique_ptr<Tile> &t:gameWord_ptr->healthPacks){
        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
        e->setPixmap(QPixmap(":/images/HealthPack.jpg").scaled(stepsize,stepsize));
        e->setPos(t->getXPos()*stepsize,t->getYPos()*stepsize);
        e->setZValue(0.8);
        graphScene->addItem(e);
        //std::cout<<t->getXPos()<< std::endl;
    }

/*    for(std::optional<std::unique_ptr<Tile>> &t:gameWord_ptr->specialFigures){
        if(t.has_value()){
            if(static_cast<Enemy>(*t.value()) == *t.value()){
                QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
                e->setPixmap(QPixmap(":/images/HealthPack.jpg").scaled(50,50));
                e->setPos(t.value()->getXPos()*50,t.value()->getYPos()*50);
                e->setZValue(0.8);
                graphScene->addItem(e);

            }
            else{
                QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
                e->setPixmap(QPixmap(":/images/Goomba.png").scaled(50,50));
                e->setPos(t.value()->getXPos()*50,t.value()->getYPos()*50);
                e->setZValue(0.8);
                graphScene->addItem(e);
            }
        }
    }

*/
    QGraphicsView *view = new QGraphicsView(graphScene);
    this->widget = view;
}

void GraphicsScene::drawEnemy(){
    for(std::unique_ptr<Enemy> &t:gameWord_ptr->enemies){
        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
        e->setPixmap(QPixmap(":/images/Goomba.png").scaled(stepsize,stepsize));
        e->setPos(t->getXPos()*50,t->getYPos()*50);
        e->setZValue(0.8);
        graphScene->addItem(e);
    }
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
    player_ptr->place(gameWord_ptr->protagonist->getXPos(), gameWord_ptr->protagonist->getYPos(),stepsize);
    graphScene->addItem(player_ptr);
}
void GraphicsScene::drawTile(){
    for(std::unique_ptr<Tile> &t:gameWord_ptr->tiles){
        specialMap * e = new specialMap(t->getXPos()*50,t->getYPos()*50,t->getValue());
        graphScene->addItem(e);
    }

}
void GraphicsScene::drawHealthPack(){
    for(std::unique_ptr<Tile> &t:gameWord_ptr->healthPacks){
        QGraphicsPixmapItem * e = new QGraphicsPixmapItem;
        e->setPixmap(QPixmap(":/images/HealthPack.jpg").scaled(50,50));
        e->setPos(t->getXPos()*50,t->getYPos()*50);
        e->setZValue(0.8);
        graphScene->addItem(e);
        std::cout<<t->getXPos()<< std::endl;
    }

}
void GraphicsScene::drawMovement(){
    // if right
    for(int y = ypos-rangeAroundPro; y<ypos+rangeAroundPro;y++ ){
        if(y >=0 && y <= rows && xpos + rangeAroundPro < columns){
            specialMap * e = new specialMap(xpos+rangeAroundPro,y,gameWord_ptr->tiles.at(xpos+rangeAroundPro+y*columns)->getValue());
            graphScene->addItem(e);
        }
    }

    // if left
    for(int y = ypos-rangeAroundPro; y<ypos+rangeAroundPro;y++ ){
        if(y >=0 && y <= rows && xpos +rangeAroundPro < columns){
            specialMap * e = new specialMap(xpos-rangeAroundPro,y,gameWord_ptr->tiles.at(xpos-rangeAroundPro+y*columns)->getValue());
            graphScene->addItem(e);
        }
    }
    // if up
    for(int x = xpos-rangeAroundPro; x<ypos+rangeAroundPro;x++ ){
        if(x >=0 && x <= columns && ypos-rangeAroundPro > 0){
            specialMap * e = new specialMap(x,ypos-rangeAroundPro,gameWord_ptr->tiles.at(x+ypos-rangeAroundPro*columns)->getValue());
            graphScene->addItem(e);
        }
    }
    // if down
    for(int x = xpos-rangeAroundPro; x<ypos+rangeAroundPro;x++ ){
        if(x >=0 && x <= columns && ypos-rangeAroundPro > 0){
            specialMap * e = new specialMap(x,ypos+rangeAroundPro,gameWord_ptr->tiles.at(x+ypos-rangeAroundPro*columns)->getValue());
            graphScene->addItem(e);
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
