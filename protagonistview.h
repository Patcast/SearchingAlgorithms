#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>

class ProtagonistView: public QGraphicsPixmapItem
{
public:

    void place(int x, int y);
    int xPos;
    int yPos;
    int StepSize = 50;
    void defeated();
};

#endif // PROTAGONISTVIEW_H
