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
<<<<<<< Updated upstream
    void drawMovement();
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;
=======
    void drawMovement(int x, int y);
    void zoomIn();
    void zoomOut();
>>>>>>> Stashed changes
};

#endif // TEXTSCENE_H
