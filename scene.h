#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QAbstractScrollArea>

class Scene
{
public:
    Scene(std::string description) : desc(description){};
    virtual void drawEnemy() = 0;
    virtual void drawProtagonist() = 0;
    virtual void drawTile() = 0;
    virtual void drawHealthPack() = 0;
    virtual void drawMovement() = 0;

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
