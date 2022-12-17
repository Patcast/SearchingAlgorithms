#ifndef TEXTSCENE_H
#define TEXTSCENE_H

#include <QString>
#include <QTextEdit>

#include "scene.h"

class TextScene : public Scene
{
public:
    TextScene();
    QString gameText;

    void drawEnemy();
    void drawProtagonist();
    void drawTile();
    void drawHealthPack();
    void drawMovement();
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;
};

#endif // TEXTSCENE_H
