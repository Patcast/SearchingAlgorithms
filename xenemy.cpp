#include "xenemy.h"
#include "qtimer.h"
#include "gameworld.h"



XEnemy::XEnemy(int xPosition, int yPosition, float strength):Enemy(xPosition, yPosition, strength)
{

}

void XEnemy::generateExplosions( )
{

//    std::vector<int> n;
//    for(int i =0;i<49;i++){
//        int nRow = Tile::getYPos()+tileOffSets3[i][0];
//        int nCol = Tile::getXPos()+tileOffSets3[i][1];
//        n.push_back(GameWorld::Instance()->getIndexFromCoordinates(nRow,nCol));
//    }
//    int rowOut


//    if(explosionIndex<MAX_EXPLODED_TILES){
//        emit explode(Tile::value,nRow,nCol);
//        QTimer::singleShot(EXPLOSION_RATE*1000, this, SLOT(generateExplosions()));
//        explosionIndex++;
//    }
//    else{
//        setDefeated(true);
//        emit dead();
//    }

}


