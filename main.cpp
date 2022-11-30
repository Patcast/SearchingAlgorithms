#include "mainwindow.h"
#include "textwindow.h"
#include <iostream>
#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;


    visual_text::TextWindow w;
    w.show();
    std::cout<<"hello Patt"<<std::endl;

    return a.exec();

//    QApplication app(argc,argv);
//    QTextEdit monoEdit;
//    QTextDocument *doc = monoEdit.document();
//    QFont font = doc->defaultFont();
//    font.setFamily("Courier New");
//    doc->setDefaultFont(font);
//    monoEdit.setReadOnly(true);

//    QString PTText = "+---+---+---+---+---+---+\n| g |   |   | x |   |   |\n+---+---+---+---+---+---+";

//    monoEdit.setPlainText(PTText);

//    monoEdit.show();
//    return app.exec();

    // QApplication a(argc, argv);
    // TwoDWindow w;
    // QGraphicsScene * scene = new QGraphicsScene();
    // scene->setSceneRect(0,0,500,600);
    // Player * pl = new Player();
    // pl->setPixmap(QPixmap(":/images/mario03.png"));
    // pl->setFlag(QGraphicsItem::ItemIsFocusable);
    // pl->setFocus();

    // scene->addItem(pl);
    // QGraphicsView * view = new QGraphicsView(scene);
    // // show the view
    // view->show();

    // return a.exec();
}
