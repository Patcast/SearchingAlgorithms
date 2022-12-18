#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "gameworld.h"
#include "protagonistview.h"
#include "scene.h"
#include <QGraphicsScene>

class GraphicsScene : public Scene
{
public:
    GraphicsScene();
    QGraphicsScene *scene;
//    std::vector<std::unique_ptr<Tile>> tiles;

    int xpos;
    int ypos;
    int rangeAroundPro;

    int rows;
    int columns;

    void drawEnemy();
    void drawProtagonist();
    void drawTile();
    void drawHealthPack();
    void drawMovement(int x, int y);
    void drawDeathEnemy(Enemy en);
    int stepsize = 50;
    void BeenThereDoneThat();
    void highLightTiles(int index);
    void showValue(int x, int y,int value);
public slots:
    virtual void zoomIn();
    virtual void zoomOut();

private:
    //QGraphicsScene * scene;
    ProtagonistView *player_ptr;
    GameWorld *gameWord_ptr;
};

#endif // GRAPHICSSCENE_H
