#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage image;
    int X,Y,R;
    QRgb red = qRgb(255,0,0);
    QRgb blue = qRgb(0,0,255);
    QRgb yellow = qRgb(255,255,0);
    explicit MainWindow(QWidget *parent = 0);

    void drawLineDDA(float x1, float y1,float x2, float y2);
    void circBresenham(int xc,int yc,int r);
    void drawCircle(int xc,int yc,int x,int y);
    void circDDA(int xc,int yc,int r);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
