#ifndef GAMESTRING_H
#define GAMESTRING_H

#include <QString>

class GameString
{
public:
    GameString(int sizeH, int sizeV, int windowSizeH = 15, int windowSizeV = 15, int windowOffsetH = 0, int windowOffsetV = 0);
    QString move(int deltaWindowOffsetH, int deltaWindowOffsetV);
    QString resize(int windowSizeH, int windowSizeV);
    QString getGameString() {return _gameString;};
    void setElement(std::pair<int,int> gameCoord, QChar element);
    void removeElement(QChar element);
    bool isVisible(std::pair<int,int> gameCoord);
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
    std::pair<int, int> _getBoardCoord(std::pair<int,int> gameCoord);
    int _getLineLength();
    int _getStartOfLine(int lineNumber);
    int _getBoxCenterInLine(int xCoord);
    int _getStringIndex(int xCoord, int yCoord);
    int _cleanOffsetH(int potOffset);
    int _cleanOffsetV(int potOffset);
    int _cleanOffset(int boardSize, int viewSize, int potOffset);
    bool _isVisible(int offset, int coord, int viewSize);

    static QString _getBoxSegment(bool starter, int line);
    static QString _getBoxLine(bool starter, int line, int amount);
    static QString _getFullBoxLine(bool starter, int amount);
    static QString _getBoxRaster(int amountX, int amountY);
};

#endif // GAMESTRING_H
