#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "graphicsscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    int heuristics;

public slots:
  void ZoomIn();
  void ZoomOut();
  void ChangeHealth(int health);
  void ChangeEnergy(int energy);
  void heuristicsValue();
};



#endif // MAINWINDOW_H
