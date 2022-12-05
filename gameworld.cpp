# include "gameworld.h"
#include <iostream>
#include <cstdlib>

// TODO:
// No need to call emplace_back, I belive that no copies are generated when moving the enemies.
// Delete TIle Composition
// Make gameworld an instance and also the protagonist.
// Check random method to initialize protagonist
// Can I use variant for the special characters.
// Check for valid index, can be improved.
// Double check that enemies and hp are placed correctly.


void GameWorld::generateWorld(QString pathToMap,int nrEnemies,int nrHeatlhPacks ,float startingEnergyProtagonist)
{
    World w= {};
    w.createWorld(pathToMap,nrEnemies,nrHeatlhPacks);
    setRowsAndColumns(w.getRows(),w.getCols());
    tiles= w.getTiles();
    std::vector<std::unique_ptr<Enemy>> enemies = w.getEnemies();
    std::vector<std::unique_ptr<Tile>> healthPacks = w.getHealthPacks();
    specialFigures.resize(tiles.size());
//    for(unsigned long i=0; i<enemies.size();i++){
//        specialFigures[getFlatIndex(enemies[i]->getXPos(),enemies[i]->getYPos())]= (std::move(enemies[i]));
//    }
//    for(unsigned long i=0; i<healthPacks.size();i++){
//        specialFigures[getFlatIndex(healthPacks[i]->getXPos(),healthPacks[i]->getYPos())]= (std::move(healthPacks[i]));
//    }
//    initializeProtagonist(startingEnergyProtagonist); // must be called at the end.
//    std::cout<<"tilesCompositionList Size: "<<specialFigures.size()<<std::endl;
}




void GameWorld::setRowsAndColumns(int newRows, int newColumns)
{
    totalRows=newRows;
    totalRows=newColumns;
}



void GameWorld::initializeProtagonist(float startingEnergy)
{
    while(protagonist==nullptr){
        int x = rand()%(totalRows);
        int y = rand()%(totalRows);
        std::cout<<"(X,Y): "<<x<<"x"<<y<<std::endl;
        if(!specialFigures[getIndexFromCoordinates(x,y)].has_value()){
            protagonist= std::make_unique<Protagonist>();
            protagonist->setEnergy(startingEnergy);
            protagonist->setXPos(x);
            protagonist->setYPos(y);
            std::cout<<"Protagonist created"<<std::endl;
        }
    }
}




std::shared_ptr<Node> GameWorld::getNode(int index)
{
    //Check if tile exists
    int row_index,col_index;
    try {
        row_index =subSetOfTiles[index]->getYPos(); // modify later to tiles.
        col_index =subSetOfTiles[index]->getXPos();
        std::shared_ptr<Node> node = std::make_shared<Node>(index,getNeighbourTileIndex(row_index,col_index));
        return node;
    } catch (const std::exception& e) {
        std::cout << e.what(); // information from error printed
        return NULL;
    }
}


std::vector<int> GameWorld::getNeighbourTileIndex(int row,int col)
{
    std::vector<int> n;
    std::cout<<" -----("<<row<<","<<col<<")-----"<<std::endl;
    for(int i =0;i<MAX_NEIGHBORS;i++){
        int nRow = row+tileOffSets[i][0];
        int nCol = col+tileOffSets[i][1];

        if(
                (nRow<totalRows)&&
                (nCol<totalColumns)&&
                (nRow>=0)&&
                (nCol>=0)
                ){
            n.push_back(getIndexFromCoordinates(nRow,nCol));
            std::cout<<" ("<<nRow<<","<<nCol<<")"<<std::endl;
        }
    }
    return n;
}

//********** TESTING**************//

void GameWorld::makeSubsetOfTiles(int rows, int columns)
{
    std::cout<<"----------- "<<std::endl;
    std::cout<<"rows "<<rows<<" cols "<<columns<<std::endl;
    for(int i =0 ; i<rows;i++){
        for(int j =0 ; j<columns;j++){
            subSetOfTiles.push_back( std::move(tiles[getIndexFromCoordinates(i,j)]));
        }
    }
    setRowsAndColumns(rows,columns);
}
void GameWorld::printTiles(int nrOfTiles)
{
    std::cout<<"(x,y)"<<std::endl;
    for(int i =0;i<nrOfTiles;i++){
       std::cout<<" ("<<tiles[i]->getYPos()<<","<<tiles[i]->getXPos()<<")"<<std::endl;
    }
}
void GameWorld::printSubSetOftiles()
{
    for (unsigned long  i=0; i <subSetOfTiles.size();i++) {
        int row_index,col_index;
        row_index =subSetOfTiles[i]->getYPos(); // modify later to tiles.
        col_index =subSetOfTiles[i]->getXPos();
        std::cout<<row_index<<" x "<<col_index<<"  index:  " <<getIndexFromCoordinates(row_index,col_index)<<std::endl;
    }
}
















