#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QColorDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    width = ui->label->width();
    height = ui->label->height();
    color= qRgb(255,0,0);
    bgcolor = Qt::white;
    firstClick = true;
    polyCompleted = false;
    image = QImage(width,height,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image));
    connect(ui->label,SIGNAL(mouse_clicked()),this,SLOT(mouse_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouse_clicked()
{
    int x,y;

    x = ui->label->x;
    y = ui->label->y;
    if (polyCompleted) {
        floodFill(x,y,bgcolor.rgb());
    }
    if (firstClick) {
        x1 = x;
        y1 = y;
        lastX = x;
        lastY = y;
        firstClick = false;
    } else {

        if (ui->label->isRight) {
            drawLineBresenhem(x1,y1,lastX,lastY);
            polyCompleted = true;
        } else {
            drawLineBresenhem(lastX,lastY,x,y);
            lastX = x;
            lastY = y;
        }
    }
}
void MainWindow::floodFill(int x,int y,QRgb newColor) {
    QRgb oldColor = image.pixel(x,y);
    if (oldColor != newColor && oldColor != color)
    {
        image.setPixel(x,y,newColor);
        floodFill(x-1,y,newColor);
        floodFill(x+1,y,newColor);
        floodFill(x,y-1,newColor);
        floodFill(x,y+1,newColor);
    }
}
void MainWindow::drawLineBresenhem(int x1, int y1, int x2, int y2){
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
        image.setPixel(x,y,color);
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
            image.setPixel(x,y,color);
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
        image.setPixel(x,y,color);
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
            image.setPixel(x,y,color);
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_btn_fill_clicked()
{
    bgcolor = QColorDialog::getColor(Qt::white,this);
}
