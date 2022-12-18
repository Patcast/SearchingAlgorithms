#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>

class ProtagonistView: public QGraphicsPixmapItem
{
public:

    void place(int x, int y,int size);
    int xPos;
    int yPos;
    int StepSize = 5;
    void defeated();
    void move(int x, int y);
    void attack();
    void heal();
};

#endif // PROTAGONISTVIEW_H
