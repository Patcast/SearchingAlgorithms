#ifndef TEXTSCENE_H
#define TEXTSCENE_H

#include <QString>
#include <QTextEdit>

#include "gamestring.h"
#include "scene.h"

class TextScene : public Scene
{
public:
    TextScene();
    GameString *gameString;

    void drawEnemy();
    void drawProtagonist();
    void drawTile();
    void drawHealthPack();
    void drawMovement();
    void zoomIn();
    void zoomOut();
};

#endif // TEXTSCENE_H
