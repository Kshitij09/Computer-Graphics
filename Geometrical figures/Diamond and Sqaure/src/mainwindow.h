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
    int X,Y;
    int SIDE;
    explicit MainWindow(QWidget *parent = 0);
    void drawLineDDA(float x1, float y1,float x2, float y2);
    void drawLineBresenhem(int x1, int y1,int x2, int y2);
    void drawSquare(int x,int y,int side);
    QPoint getMidpoint(float x1,float y1,float x2,float y2);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
