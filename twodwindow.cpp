#include "twodwindow.h"
#include "ui_twodwindow.h"

namespace visual_2d{
    TwoDWindow::TwoDWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::TwoDWindow)
    {
        ui->setupUi(this);
    }

    TwoDWindow::~TwoDWindow()
    {
        delete ui;
    }
}


