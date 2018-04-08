#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    X = 150;      //Can be read from user
    Y = 150;      //Can be read from user
    SIDE = 300;   //Can be read from user
    drawSquare(X,Y,SIDE);
    QPoint mid1 = getMidpoint(X,Y,X,Y+SIDE);
    QPoint mid2 = getMidpoint(X,Y,X+SIDE,Y);
    QPoint mid3 = getMidpoint(X+SIDE,Y,X+SIDE,Y+SIDE);
    QPoint mid4 = getMidpoint(X,Y+SIDE,X+SIDE,Y+SIDE);

    //Drawing diamond
    drawLineDDA(mid1.x(),mid1.y(),mid2.x(),mid2.y());
    drawLineDDA(mid2.x(),mid2.y(),mid3.x(),mid3.y());
    drawLineDDA(mid3.x(),mid3.y(),mid4.x(),mid4.y());
    drawLineDDA(mid1.x(),mid1.y(),mid4.x(),mid4.y());

    //As Inner polygon is square, all sides will be of same length
    QPoint inner1 = getMidpoint(mid1.x(),mid1.y(),mid2.x(),mid2.y());
    QPoint inner2 = getMidpoint(mid2.x(),mid2.y(),mid3.x(),mid3.y());

    drawSquare(inner1.x(),inner1.y(),inner2.x()-inner1.x());
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::drawLineDDA(float x1, float y1, float x2, float y2){
    QRgb red;
    red = qRgb(255,0,0);

    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    float xInc = dx / length;
    float yInc = dy / length;

    float X = x1;
    float Y = y1;
    image.setPixel(X,Y,red);
    for (int i=1; i <= length; i++){
        X += xInc;
        Y += yInc;
        image.setPixel(X,Y,red);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::drawLineBresenhem(int x1, int y1, int x2, int y2){
    QRgb blue = qRgb(0,0,255);
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x,y,xEnd,yEnd;

    //Decision variable p for determing value of y
    bool incrY = false;
    bool incrX = false;
    int p = 2 * dy - dx;
    if (dx > dy){
        //Slope is below 45 degree, x will always increament and y will depend upon p
        //Deciding initial point
        if (x1 > x2){
            x = x2;
            y = y2;
            if (y < y1)
                incrY = true;
            xEnd = x1;
        }else{
            x = x1;
            y = y1;
            if (y < y2)
                incrY = true;
            xEnd = x2;
        }
        image.setPixel(x,y,blue);
        while(x < xEnd){
            x++;
            if (p < 0){
                // Error is less than zero, no need to inreament y
                p += 2 * dy;
            }else{
                //Need to increament y and reset p
                p = p + (2 * (dy - dx));
                if(incrY)
                    y++;
                else
                    y--;
            }
            image.setPixel(x,y,blue);
        }

    }else{
        //Slope is above 45 degree, y will always increament and x will depend upon p
        //Deciding initial point
        if (y1 > y2){
            x = x2;
            y = y2;
            if (x < x1)
                incrX = true;
            yEnd = y1;
        }else{
            x = x1;
            y = y1;
            if (x < x2)
                incrX = true;
            yEnd = y2;
        }
        image.setPixel(x,y,blue);
        while(y < yEnd){
            y++;
            if (p < 0){
                // Error is less than zero, no need to inreament y
                p += 2 * dx;
            }else{
                //Need to increament y and reset p
                p = p + (2 * (dx - dy));
                if(incrX)
                    x++;
                else
                    x--;
            }
            image.setPixel(x,y,blue);
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::drawSquare(int x, int y, int side)
{
    drawLineBresenhem(x,y,x+side,y);
    drawLineBresenhem(x+side,y,x+side,y+side);
    drawLineBresenhem(x,y+side,x+side,y+side);
    drawLineBresenhem(x,y,x,y+side);
}

QPoint MainWindow::getMidpoint(float x1, float y1, float x2, float y2)
{
    QPoint mid;
    mid.setX((x1+x2)/2);
    mid.setY((y1+y2)/2);
    return mid;
}
