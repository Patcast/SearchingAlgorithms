#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "gameworld.h"
#include "protagonistview.h"
#include "scene.h"

class GraphicsScene : public Scene
{
public:
    GraphicsScene();
    QGraphicsScene *graphScene;

    void drawEnemy();
    void drawProtagonist();
    void drawTile();
    void drawHealthPack();
    void drawMovement();
    void drawDeathEnemy(Enemy en);

public slots:
    void zoomIn();
    void zoomOut();

private:
    QGraphicsScene * scene;
    ProtagonistView *player_ptr;
    GameWorld *gameWord_ptr;
};

#endif // GRAPHICSSCENE_H
