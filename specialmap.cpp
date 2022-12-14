#include "specialmap.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QtGui>
#include <QColor>


specialMap::specialMap(int x, int y, float value)
{
    xPos = x * size;
    yPos = y * size;
    Value = value;
    setRect(xPos,yPos,size,size);
    setBrush(QBrush(QColor(255, 0, 0, 255*value)));
}
