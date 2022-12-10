#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "gameworld.h"
#include "protagonistview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //QGraphicsScene * scene;
    ProtagonistView player;
    GameWorld * gameWord_ptr;
public slots:
  void zoomIn();
  void zoomOut();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
