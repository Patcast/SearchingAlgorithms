#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "gameworld.h"
#include "protagonistview.h"
#include "scene.h"
#include <QGraphicsScene>
#include <QMouseEvent>

class GraphicsScene : public Scene
{
public:
    GraphicsScene();
    QGraphicsScene *scene;
//    std::vector<std::unique_ptr<Tile>> tiles;

    int xpos;
    int ypos;
    int rangeAroundPro;
    QGraphicsView *view;

    int rows;
    int columns;
    void mousePressEvent(QMouseEvent * event);
    void spreadPoison(int x, int y);
    void drawDeathPEnemy(int x, int y);
    void drawEnemy(int xPos, int yPos);
    void drawPEnemy(int xPos, int yPos);
    void drawXEnemy(int xPos, int yPos);
    void drawProtagonist(int xPos, int yPos);
    void drawTile();
    void drawHealthPack(int xPos, int yPos);
    void drawMovement(int xPos, int yPos);
    void drawDeathEnemy(int x, int y);
    void drawEmptyHealtPack(int x, int y);
    int stepsize = 50;
    void BeenThereDoneThat();
    void highLightTiles(int index);
    void showValue(int x, int y,int value);
    void drawAll();
    void drawPoisonous(int xPos, int yPos);
    void drawExplosive(int xPos, int yPos);
    void removePoisonous(int xPos, int yPos);

public slots:
    void zoomIn();
    void zoomOut();

private:
    ProtagonistView *player_ptr;
    GameWorld *gameWord_ptr;
};

#endif // GRAPHICSSCENE_H
