#include "graphicsscene.h"
#include "enemyview.h"
#include "healthpackview.h"
#include "specialmap.h"
#include <QRect>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsTextItem>



GraphicsScene::GraphicsScene() : Scene("2d")
{


    gameWord_ptr = GameWorld::Instance(":/images/maze2.png", 60, 20, 100.0);
    player_ptr = new ProtagonistView();
    columns = gameWord_ptr->getTotalColumns();
    rows = gameWord_ptr->getTotalRows();
    graphScene = new QGraphicsScene();
    QGraphicsPixmapItem *world = new QGraphicsPixmapItem();
    world->setPixmap(QPixmap(":/images/maze2.png").scaledToHeight(stepsize*rows));
    //stepsize*rows
    world->setZValue(0.5);
    graphScene->addItem(world);

/*  test showValue
 *  QGraphicsTextItem * text = new QGraphicsTextItem();
    int value = 15;
    text->setPlainText(QVariant(value).toString());
    text->setX(8*50);
    text->setY(5*50-25);
    text->setZValue(1.2);
    QColor color(255, 0, 0); // red
    text->setDefaultTextColor(color);
    graphScene->addItem(text);
*/


    //player_ptr->place(gameWord_ptr->protagonist->getXPos(), gameWord_ptr->protagonist->getYPos(),stepsize);
    player_ptr->place(6,10,stepsize);
    player_ptr->setZValue(1);
    graphScene->addItem(player_ptr);
    BeenThereDoneThat();

    int index = 6*columns+8;
    highLightTiles(index);
    index = 5*columns + 8;
    highLightTiles(index);
    highLightTiles(10*columns+6);

    showValue(8,5,45);
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

/*    for(std::optional<std::unique_ptr<Tile>> &t:gameWord_ptr->specialFigures){
        if(t.has_value()){
            if(dynamic_cast<Enemy>(*t.value()) == ){
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
    drawEnemy();


    QGraphicsView *view = new QGraphicsView(graphScene);
    this->widget = view;
}

void GraphicsScene::drawEnemy(){
    int i = 0;
    for(int x = 0; x<columns; x++){
        for(int y = 0; y<rows; y++){
            if(gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr().get() != nullptr){
                if(Enemy * enemyReference = dynamic_cast<Enemy*>(gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr().get())){
                    enemyView *e = new enemyView();
                    e->place(gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getXPos(),gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getYPos(),stepsize);
                    showValue(gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getXPos(),gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getYPos(),gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getValue());
                    graphScene->addItem(e);
                    i++;
                    }
                else{
                    healthPackView *e = new healthPackView();
                    e->place(gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getXPos(),gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getYPos(),stepsize);
                    showValue(gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getXPos(),gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getYPos(),gameWord_ptr->nodes[x+y*columns]->getSpecialFigure_ptr()->getValue());
                    graphScene->addItem(e);
                    }
                }
            }
        }
    std::cout<<i<< std::endl;
}
void GraphicsScene::drawDeathEnemy(Enemy en){
    enemyView * e = new enemyView();
    e->defeated(en.getXPos(),en.getYPos());
    graphScene->addItem(e);
}

void GraphicsScene::BeenThereDoneThat()
{
    QGraphicsRectItem * tile = new QGraphicsRectItem();
    tile->setRect(player_ptr->xPos,player_ptr->yPos,stepsize,stepsize);
    tile->setBrush(QBrush(QColor(50, 124,252,100)));
    tile->setZValue(0.7);
    graphScene->addItem(tile);
}

void GraphicsScene::highLightTiles(int index)
{
    QGraphicsRectItem * tile = new QGraphicsRectItem();
    tile->setRect(stepsize* index%columns,stepsize* index/columns,stepsize,stepsize);
    tile->setBrush(QBrush(QColor(50, 250,128,100)));
    tile->setZValue(0.7);
    graphScene->addItem(tile);
}

void GraphicsScene::showValue(int x, int y, int value)
{
    QGraphicsTextItem * text = new QGraphicsTextItem();
    text->setPlainText(QVariant(value).toString());
    text->setX(x*stepsize);
    text->setY(y*stepsize-25);
    text->setZValue(1.2);
    QColor color(255, 0, 0); // red
    text->setDefaultTextColor(color);
    graphScene->addItem(text);
}


void GraphicsScene::drawProtagonist(){
    player_ptr = new ProtagonistView();
//    player_ptr->place(gameWord_ptr->getProtagonist()->getXPos(), gameWord_ptr->getProtagonist()->getYPos(),stepsize);
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
//        healthPackView * e = new healthPackView();
//        e.place(e.getYPos(),e.getyPos(),stepsize);
//        graphScene->addItem(e);
//        std::cout<<t->getXPos()<< std::endl;
//    }
}
void GraphicsScene::drawMovement(){
    player_ptr->move(gameWord_ptr->protagonist->getXPos(),gameWord_ptr->protagonist->getYPos());


/*    // if right
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
*/
}
void GraphicsScene::zoomIn(){
    QGraphicsView* viewWidget = static_cast<QGraphicsView*>(this->widget);
    viewWidget->scale(1.2, 1.2);
}
void GraphicsScene::zoomOut(){
    QGraphicsView* viewWidget = static_cast<QGraphicsView*>(this->widget);
    viewWidget->scale(0.8, 0.8);
}


