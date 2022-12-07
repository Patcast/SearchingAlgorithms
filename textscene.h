#ifndef TEXTSCENE_H
#define TEXTSCENE_H

#include <QString>
#include <QTextEdit>

#include "scene.h"

class TextScene : public Scene
{
public:
    TextScene();
    QString gameText;
};

#endif // TEXTSCENE_H
