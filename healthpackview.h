#ifndef HEALTHPACKVIEW_H
#define HEALTHPACKVIEW_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>

class healthPackView:public QGraphicsPixmapItem
{
public:

    void place(int x, int y,int size);
    int xPos;
    int yPos;
    int StepSize = 5;
    void defeated();
};

#endif // HEALTHPACKVIEW_H
