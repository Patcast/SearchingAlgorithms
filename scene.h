#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QAbstractScrollArea>

class Scene
{
public:
    Scene(std::string description) : desc(description){};
    virtual void drawEnemy(int xPos, int yPos) = 0;
    virtual void drawPEnemy(int xPos, int yPos) = 0;
    virtual void drawXEnemy(int xPos, int yPos) = 0;
    virtual void drawProtagonist(int xPos, int yPos) = 0;
    virtual void drawTile() = 0;
    virtual void drawHealthPack(int xPos, int yPos) = 0;
    virtual void drawMovement(int xPos, int yPos) = 0;
    virtual void drawHighlight(int xPos, int yPos) = 0;
    virtual void removeHighlight();

    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;
    std::string getDescription() { return desc; };
    QWidget *getQView() { return widget; };
    bool operator == (const std::string s) const {return s == desc; }


protected:
    QWidget *widget;
    std::string desc;
};

#endif // ABSTRACTVIEW_H
