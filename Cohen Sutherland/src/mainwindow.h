#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clicklabel.h"
#include <vector>
#include <QPainter>
#include <QPen>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::vector<QPoint> points;
    int xL,yL,xH,yH;    //Window co-ordinates
    int width,height;
    QImage image;
    QImage newImage;
    int x,y;            //For window
    int x1,y1;          //For line drawing
    bool firstClick;
    explicit MainWindow(QWidget *parent = 0);
    void drawLineBresenham(int x1, int y1,int x2, int y2,QRgb color=qRgb(0,0,255));
    void drawRectangle(int x1, int y1, int x2, int y2);
    int* getOutcode(QPoint point);
    QPoint getIntersect(QPoint A,QPoint B,int i);
    int case_test(int* oc1,int* oc2);
    ~MainWindow();

private slots:
    void mouse_position();
    void mouse_clicked();
    void mouse_released();
    void on_btn_clip_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
