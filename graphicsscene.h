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
    QGraphicsScene *graphScene;
//    std::vector<std::unique_ptr<Tile>> tiles;

    int xpos;
    int ypos;
    int rangeAroundPro;

    int rows;
    int columns;

    void drawEnemy(int xPos, int yPos);
    void drawPEnemy(int xPos, int yPos);
    void drawXEnemy(int xPos, int yPos);
    void drawProtagonist(int xPos, int yPos);
    void drawTile();
    void drawHealthPack(int xPos, int yPos);
    void drawMovement(int xPos, int yPos);
    void drawDeathEnemy(Enemy en);
    int stepsize = 50;
    void BeenThereDoneThat();
    void highLightTiles(int index);
    void showValue(int x, int y,int value);

public slots:
    void zoomIn();
    void zoomOut();

private:
    ProtagonistView *player_ptr;
    GameWorld *gameWord_ptr;
};

#endif // GRAPHICSSCENE_H
