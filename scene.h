#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QAbstractScrollArea>

class Scene : QWidget
{
public:
    Scene(std::string desc);
    virtual void drawEnemy() = 0;
    virtual void drawProtagonist() = 0;
    virtual void drawTile() = 0;
    virtual void drawHealthPack() = 0;
    virtual void drawMovement() = 0;
    std::string getDescription() { return desc; };
    std::shared_ptr<QWidget> getQView() { return widget; };


protected:
    std::shared_ptr<QWidget> widget;
    std::string desc;
};

#endif // ABSTRACTVIEW_H
