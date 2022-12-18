#include "graphicsscene.h"
#include "enemyview.h"
#include "penemyview.h"
#include "healthpackview.h"
#include "qtimer.h"
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
#include <QTimer>

GraphicsScene::GraphicsScene() : Scene("2d")
{
    player_ptr = new ProtagonistView();
    columns =  GameWorld::Instance()->getTotalColumns();
    rows = GameWorld::Instance()->getTotalRows();
    scene = new QGraphicsScene();

    player_ptr = new ProtagonistView();
        columns =  GameWorld::Instance()->getTotalColumns();
        rows = GameWorld::Instance()->getTotalRows();
        scene = new QGraphicsScene();
        QGraphicsPixmapItem * world = new QGraphicsPixmapItem();
        world->setPixmap(QPixmap(GameWorld::Instance()->getImagePath()).scaledToHeight(stepsize*rows));
        //stepsize*rows
        world->setZValue(0.5);
        scene->addItem(world);

//    stepsize = 1;
//    QGraphicsPixmapItem *world = new QGraphicsPixmapItem();
//    world->setPixmap(QPixmap(GameWorld::Instance()->getImagePath()));
//    //world->setScale(stepsize);
//    world->setZValue(0.5);
//    scene->addItem(world);

    drawProtagonist(GameWorld::Instance()->getProtagonist()->getXPos(),GameWorld::Instance()->getProtagonist()->getYPos());




    //player_ptr->place(gameWord_ptr->protagonist->getXPos(), gameWord_ptr->protagonist->getYPos(),stepsize);
    player_ptr->place(GameWorld::Instance()->getProtagonist()->getXPos(),GameWorld::Instance()->getProtagonist()->getYPos(),stepsize);
    player_ptr->setZValue(1);
    scene->addItem(player_ptr);

    drawAll();
//    drawDeathEnemy(1, 1);
//    drawEmptyHealtPack(0, 1);
//    drawDeathPEnemy(4,4);
    view = new QGraphicsView(scene);
    this->widget = view;
    view->centerOn(player_ptr);
}

void GraphicsScene::mousePressEvent(QMouseEvent *event)
{
    auto place = view->mapToScene(event->pos());
    std::cout<<place.rx()<<  place.ry()<< std::endl;
}

void GraphicsScene::spreadPoison(int x, int y)
{
    QGraphicsRectItem * tile = new QGraphicsRectItem();
    tile->setRect(x*stepsize,y*stepsize,stepsize,stepsize);
    tile->setBrush(QBrush(QColor(0,255,127,50)));
    tile->setZValue(0.6);
    scene->addItem(tile);
}

void GraphicsScene::drawPEnemy(int xPos, int yPos){

}

void GraphicsScene::drawXEnemy(int xPos, int yPos){

}

void GraphicsScene::drawEnemy(int xPos, int yPos){
//    for(unsigned long i=0; i<GameWorld::Instance()->getSpecialFiguresVector().size();i++){
//        if(Enemy* enemyReference =dynamic_cast<Enemy*>(GameWorld::Instance()->getSpecialFiguresVector()[i].get())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
//            if(PEnemy* enemyReference =dynamic_cast<PEnemy*>(GameWorld::Instance()->getSpecialFiguresVector()[i].get())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer

//            }
//            else{
//                enemyView *e = new enemyView();
//                e->place(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(),stepsize);
//                showValue(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getValue());
//                scene->addItem(e);
//            }
//        }
//        else
//        {
//            healthPackView * p = new healthPackView();
//            p->place(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(),stepsize);
//            showValue(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getValue());
//            scene->addItem(p);
//        }
//    }

//    for(int x = 0; x<columns; x++){
//        for(int y = 0; y<rows; y++){
//            if( GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr().get() != nullptr){
//                if(Enemy * enemyReference = dynamic_cast<Enemy*>( GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr().get())){
//                    enemyView *e = new enemyView();
//                    e->place( GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getXPos(), GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getYPos(),stepsize);
//                    showValue( GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getXPos(), GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getYPos(), GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getValue());
//                    graphScene->addItem(e);
//                    i++;
//                    }
//                else{
//                    healthPackView *e = new healthPackView();
//                    e->place( GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getXPos(), GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getYPos(),stepsize);
//                    showValue( GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getXPos(), GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getYPos(),GameWorld::Instance()->nodes[x+y*columns]->getSpecialFigure_ptr()->getValue());
//                    graphScene->addItem(e);
//                    }
//                }
//            }
//        }
}


void GraphicsScene::drawDeathEnemy(int x, int y){
    enemyView * e = new enemyView();
    e->defeated(x,y,stepsize);
    scene->addItem(e);
    player_ptr->attack();
}

void GraphicsScene::drawDeathPEnemy(int x, int y){
    PEnemyView * e = new PEnemyView();
    e->defeated(x,y,stepsize);
    scene->addItem(e);
    for(int i = x-1; i<=x+1;i++){
        for(int j = y-1; j<=y+1;j++){
            spreadPoison(i,j);
        }
    }

}

void GraphicsScene::drawEmptyHealtPack(int x, int y)
{
    healthPackView * e = new healthPackView();
    e->defeated(x,y,stepsize);
    scene->addItem(e);
    player_ptr->heal();
}

void GraphicsScene::BeenThereDoneThat()
{
    QGraphicsRectItem * tile = new QGraphicsRectItem();
    tile->setRect(player_ptr->xPos,player_ptr->yPos,stepsize,stepsize);
    tile->setBrush(QBrush(QColor(50, 124,252,20)));
    tile->setZValue(0.7);
    scene->addItem(tile);
}

void GraphicsScene::highLightTiles(int index)
{
    QGraphicsRectItem * tile = new QGraphicsRectItem();
    tile->setRect(stepsize* index%columns,stepsize* index/columns,stepsize,stepsize);
    tile->setBrush(QBrush(QColor(50, 250,128,100)));
    tile->setZValue(0.7);
    scene->addItem(tile);
}

void GraphicsScene::showValue(int x, int y, int value)
{
    QGraphicsTextItem * text = new QGraphicsTextItem();
    text->setPlainText(QVariant(value).toString());
    text->setX(x*stepsize);
    text->setY(y*stepsize-25);
    text->setZValue(1.2);
    QFont font = text->font();
    font.setPointSize(12);  // Set the font size to 12 points
    text->setFont(font);
    QColor color(255, 150, 0);
    text->setDefaultTextColor(color);
    scene->addItem(text);
}

void GraphicsScene::drawAll()
{
    for(unsigned long i=0; i<GameWorld::Instance()->getSpecialFiguresVector().size();i++){
            if(Enemy* enemyReference =dynamic_cast<Enemy*>(GameWorld::Instance()->getSpecialFiguresVector()[i].get())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
                if(PEnemy* enemyReference =dynamic_cast<PEnemy*>(GameWorld::Instance()->getSpecialFiguresVector()[i].get())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
                    PEnemyView *e = new PEnemyView();
                    e->place(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(),stepsize);
                    showValue(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getValue());
                    scene->addItem(e);
                }
                else{
                    enemyView *e = new enemyView();
                    e->place(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(),stepsize);
                    showValue(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getValue());
                    scene->addItem(e);
                }
            }
            else
            {
                healthPackView * p = new healthPackView();
                p->place(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(),stepsize);
                showValue(GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getXPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getYPos(), GameWorld::Instance()->getSpecialFiguresVector()[i].get()->getValue());
                scene->addItem(p);
            }
    }
}

void GraphicsScene::drawDeadEnemy(int type, int x, int y){
    if(type == 0){
        drawDeathEnemy(x,y);
    }
    if(type == 1){

        drawDeathPEnemy(x,y);
    }
    else{
        std::cout<<"XEnemy"<< std::endl;
    }

}
void GraphicsScene::drawProtagonist(int xPos, int yPos){
    player_ptr->place(xPos,yPos,stepsize);
    player_ptr->setZValue(1);
    scene->addItem(player_ptr);
    BeenThereDoneThat();
}
void GraphicsScene::drawTile(){
    QString s =GameWorld::Instance()->getImagePath();
    QString q = ":/images/maze3.png";
    int x = QString::compare(s, q, Qt::CaseInsensitive);
    if(x==0){
        stepsize = 1;
        QGraphicsPixmapItem *world = new QGraphicsPixmapItem();
        world->setPixmap(QPixmap(GameWorld::Instance()->getImagePath()));
        //world->setScale(stepsize);
        world->setZValue(0.5);
        scene->addItem(world);
    }
    else{
        stepsize = 50;
        QGraphicsPixmapItem *world = new QGraphicsPixmapItem();
        world->setPixmap(QPixmap(GameWorld::Instance()->getImagePath()));
        world->setScale(stepsize);
        world->setZValue(0.5);
        scene->addItem(world);

    }
}
void GraphicsScene::drawHealthPack(int xPos, int yPos){
//    for(std::unique_ptr<Tile> &t:gameWord_ptr->healthPacks){
//        healthPackView * e = new healthPackView();
//        e.place(e.getYPos(),e.getyPos(),stepsize);
//        graphScene->addItem(e);
//        std::cout<<t->getXPos()<< std::endl;
//    }
}
void GraphicsScene::drawMovement(int xPos, int yPos){
    player_ptr->move( GameWorld::Instance()->protagonist->getXPos(), GameWorld::Instance()->protagonist->getYPos());
    BeenThereDoneThat();
    view->centerOn(player_ptr);

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

void GraphicsScene::drawHighlight(int xPos, int yPos) {

}

void GraphicsScene::removeHighlight(int xPos, int yPos) {

}

void GraphicsScene::drawPoisonous(int xPos, int yPos) {

}

void GraphicsScene::drawExplosive(int xPos, int yPos) {

}

void GraphicsScene::removePoisonous(int xPos, int yPos) {

}

