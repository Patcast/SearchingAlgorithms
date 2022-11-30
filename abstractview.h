#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QAbstractScrollArea>

class AbstractView
{
public:
    AbstractView(std::string desc, QAbstractScrollArea &QASA);
    virtual void doMove() = 0;
    std::string getDescription() { return desc; };
    QAbstractScrollArea& getQView() { return QViewObject; };

protected:
    QAbstractScrollArea &QViewObject;
    std::string desc;
};

#endif // ABSTRACTVIEW_H
