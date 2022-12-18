#ifndef TEXTSCENE_H
#define TEXTSCENE_H

#include <QString>
#include <QTextEdit>

#include "gamestring.h"
#include "scene.h"
#include "world.h"

class TextScene : public Scene
{
public:
    TextScene();
    std::shared_ptr<GameString> gameString;

    void drawEnemy(int xPos, int yPos);
    void drawEnemy(std::pair<int,int> pos);
    void drawPEnemy(int xPos, int yPos);
    void drawPEnemy(std::pair<int,int> pos);
    void drawProtagonist(int xPos, int yPos);
    void drawProtagonist(std::pair<int,int> pos);
    void drawTile();
    void drawHealthPack(int xPos, int yPos);
    void drawHealthPack(std::pair<int,int> pos);
    void drawMovement(int xPos, int yPos);
    void zoomIn();
    void zoomOut();
    void drawElements(const std::vector<std::shared_ptr<Tile>> &elements);

private:
    void _generate(int hSize, int vSize, int DEFAULT_HSIZE, int DEFAULT_VSIZE,
                   const std::vector<std::shared_ptr<Tile>> &elements,
                   std::pair<int,int> protPos);
};

#endif // TEXTSCENE_H
