#include "xenemy.h"
#include "qtimer.h"



XEnemy::XEnemy(int xPosition, int yPosition, float strength):Enemy(xPosition, yPosition, strength)
{

}

void XEnemy::generateExplosions( )
{
    int nRow,nCol;
    nRow = Tile::getYPos()+explosionOffSets[explosionIndex][0];
    nCol = Tile::getXPos()+explosionOffSets[explosionIndex][1];

    if(explosionIndex<MAX_EXPLODED_TILES){
        emit explode(Tile::value,nRow,nCol);
        QTimer::singleShot(EXPLOSION_RATE*1000, this, SLOT(generateExplosions()));
        explosionIndex++;
    }
    else{
        setDefeated(true);
        emit dead();
    }

}


