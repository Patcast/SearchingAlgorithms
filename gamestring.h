#ifndef GAMESTRING_H
#define GAMESTRING_H

#include <QString>


class GameString
{
public:
    GameString(int sizeH, int sizeV, int windowSizeH = 10, int windowSizeV = 10, int windowOffsetH = 0, int windowOffsetV = 0);
    QString move(int deltaWindowOffsetH, int deltaWindowOffsetV);
    QString resize(int windowSizeH, int windowSizeV);
private:
    int TILE_WIDTH = 3;
    int TILE_HEIGHT = 1;
    int _sizeH;
    int _sizeV;
    int _windowSizeH;
    int _windowSizeV;
    int _windowOffsetH;
    int _windowOffsetV;
    QString _gameString;
    // std::vector<GroupTile*> _board;
    QString _generate();
    void _prepareGameString();
    void _generateBorders();
};

#endif // GAMESTRING_H
