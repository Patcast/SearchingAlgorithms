#ifndef PENEMYVIEW_H
#define PENEMYVIEW_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>


class PEnemyView: public QGraphicsPixmapItem
{
public:
    void place(int x, int y,int size);
    int xPos;
    int yPos;
    int StepSize = 5;
    void defeated(int x, int y, int size);
};


#endif // PENEMYVIEW_H
