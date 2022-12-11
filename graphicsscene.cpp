#include "graphicsscene.h"
#include "player.h"
#include <QGraphicsScene>
#include <QGraphicsView>

GraphicsScene::GraphicsScene() : Scene("2d")
{
    QGraphicsScene *graphScene = new QGraphicsScene();
    graphScene->setSceneRect(0,0,490,490);
    Player *pl = new Player();
    pl->setPixmap(QPixmap(":/images/mario03.png"));
    pl->setFlag(QGraphicsItem::ItemIsFocusable);
    pl->setFocus();
    graphScene->addItem(pl);
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
