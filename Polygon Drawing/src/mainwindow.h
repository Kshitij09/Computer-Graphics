#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clicklabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage image;
    QColor color;
    int width,height;
    bool firstClick;
    int x1,y1;
    int lastX,lastY;
    explicit MainWindow(QWidget *parent = 0);
    void drawLineBresenhem(int x1, int y1, int x2, int y2,QRgb color = qRgb(255,0,0));
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void mouse_clicked();
    void mouse_right_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
