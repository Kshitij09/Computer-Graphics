#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = QImage(ui->label->width(),
                   ui->label->height(),
                   QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image));

    //Drawing figure
    X = 350;        //Can be read from user
    Y = 350;        //Can be read from user
    R = 200;        //Can be read from user

    //Circumcircle with radius R
    circBresenham(X,Y,R);

    //radius and side of triangle bisects each other
    /*By pythagoras theorem, side/2 (s) of triangle is
     * s = sqrt(3)/2*radius;
     *            /|
     *           / |
     *          /  |
     *         /   |
     *      R /    |
     *       /     |R/2
     *      /      |
     *     /       |
     *    /________|
     *        s
     */
    float s = sqrt(3)/2*R;

    //triangle's base
    drawLineDDA(X-s,Y+(R/2),X+s,Y+(R/2));

    //top point of triangle is known (x,y-r)
    drawLineDDA(X-s,Y+(R/2),X,Y-R);
    drawLineDDA(X+s,Y+(R/2),X,Y-R);

    //Inscribed circle with radius R/2
    circDDA(X,Y,R/2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineDDA(float x1, float y1, float x2, float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    float xInc = dx / length;
    float yInc = dy / length;

    float X = x1;
    float Y = y1;
    image.setPixel(X,Y,blue);
    for (int i=1; i <= length; i++){
        X += xInc;
        Y += yInc;
        image.setPixel(X,Y,blue);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::circBresenham(int xc, int yc,int r)
{
    //initial Conditions
    int x = 0;
    int y = r;
    int d = 3 - (2 * r);
    while(y >= x) {
        /*For each pixel we will draw
         * all eight pixels*/
        drawCircle(xc,yc,x,y);
        x++;
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        drawCircle(xc,yc,x,y);
    }
}
void MainWindow::drawCircle(int xc, int yc, int x, int y) {
    image.setPixel(xc+x,yc+y,red);
    image.setPixel(xc-x,yc+y,red);
    image.setPixel(xc+x,yc-y,red);
    image.setPixel(xc-x,yc-y,red);
    image.setPixel(xc+y,yc+x,red);
    image.setPixel(xc-y,yc+x,red);
    image.setPixel(xc+y,yc-x,red);
    image.setPixel(xc-y,yc-x,red);
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::circDDA(int xc, int yc, int r)
{
    //Initialization
    float xc1,xc2,yc1,yc2,sx,sy;
    xc1 = r;
    yc1 = 0;
    sx = xc1;
    sy = yc1;
    int val = 0;
    int i;
    for (i = 0; val < r; ++i)
        val = pow(2,i);
    double eps = 1/pow(2,i-1);
    do {
        xc2 = xc1 + yc1 * eps;
        yc2 = yc1 - eps * xc2;
        image.setPixel(xc+xc2,yc-yc2,yellow);
        xc1 = xc2;
        yc1 = yc2;
    } while((yc1-sy)<eps || (sx-xc1)>eps);
    ui->label->setPixmap(QPixmap::fromImage(image));
}
