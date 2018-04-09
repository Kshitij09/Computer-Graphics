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
    X = 350;
    Y = 300;
    R = 200;
    //Main circle
    circBresenham(X,Y,R);

    //Circles at the corners
    circBresenham(X,Y-R,R/2);
    circBresenham(X-R,Y,R/2);
    circBresenham(X+R,Y,R/2);
    circBresenham(X,Y+R,R/2);


    //Making the main circle opaque
    floodFill(X,Y,white);
    floodFill(X,Y-R+5,white);
    floodFill(X-R+5,Y,white);
    floodFill(X+R-5,Y,white);
    floodFill(X,Y+R-5,white);
    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    image.setPixel(xc+x,yc+y,white);
    image.setPixel(xc-x,yc+y,white);
    image.setPixel(xc+x,yc-y,white);
    image.setPixel(xc-x,yc-y,white);
    image.setPixel(xc+y,yc+x,white);
    image.setPixel(xc-y,yc+x,white);
    image.setPixel(xc+y,yc-x,white);
    image.setPixel(xc-y,yc-x,white);
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::floodFill(int x,int y,QRgb newColor) {
    QRgb oldColor = image.pixel(x,y);
    if (oldColor != newColor)
    {
        //qDebug() << x << " " << y;
        image.setPixel(x,y,newColor);
        floodFill(x-1,y,newColor);
        floodFill(x+1,y,newColor);
        floodFill(x,y-1,newColor);
        floodFill(x,y+1,newColor);
    }
}
