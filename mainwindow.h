#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "commands.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>

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
    void setSignalsFromProtagnist();
    bool eventFilter(QObject* obj, QEvent *event);

signals:
    void arrowPress(moveDirection direction);

public slots:
  void ChangeHealth(int health);
  void ChangeEnergy(int energy);
  void heuristicsValue();
  void ChangeHealthNumber(int);
  void showWin();
  void showLoss();
};



#endif // MAINWINDOW_H
