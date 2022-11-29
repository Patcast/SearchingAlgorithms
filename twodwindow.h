#ifndef TWODWINDOW_H
#define TWODWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class TwoDWindow; }
QT_END_NAMESPACE
namespace visual_2d{
    class TwoDWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        TwoDWindow(QWidget *parent = nullptr);
        ~TwoDWindow();


    private:
        Ui::TwoDWindow *ui;
    };
}

#endif // TWODWINDOW_H
