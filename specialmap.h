#ifndef SPECIALMAP_H
#define SPECIALMAP_H


#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsRectItem>

class specialMap: public QGraphicsRectItem
{
public:
    specialMap(int x, int y, float value);
    int xPos = 0;
    int yPos = 0;
    int size = 25;
    int Value;
    int range = 50;
};

#endif // SPECIALMAP_H
