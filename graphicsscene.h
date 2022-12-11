#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "scene.h"

class GraphicsScene : public Scene
{
public:
    GraphicsScene();

    void drawEnemy();
    void drawProtagonist();
    void drawTile();
    void drawHealthPack();
    void drawMovement();
};

#endif // GRAPHICSSCENE_H
