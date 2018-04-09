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
    int X,Y,R;
    QImage image;
    QRgb white = qRgb(255,255,255);
    explicit MainWindow(QWidget *parent = 0);
    void circBresenham(int xc, int yc,int r);
    void drawCircle(int xc, int yc, int x, int y);
    void floodFill(int x,int y,QRgb newColor);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
