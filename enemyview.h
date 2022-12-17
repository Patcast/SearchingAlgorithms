#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>

class enemyView: public QGraphicsPixmapItem
{
public:
    void place(int x, int y,int size);
    int xPos;
    int yPos;
    int StepSize = 5;
    void defeated(int x, int y);
};

#endif // ENEMYVIEW_H
