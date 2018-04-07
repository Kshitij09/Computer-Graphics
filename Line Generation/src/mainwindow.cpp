#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    width = ui->lbl_draw->width();
    height = ui->lbl_draw->height();
    image = QImage(width,height,QImage::Format_RGB888);
    ui->lbl_draw->setPixmap(QPixmap::fromImage(image));
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
    ui->lbl_draw->setPixmap(QPixmap::fromImage(image));
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
        qDebug() << "Case 1: Slope below 45";
        //Deciding initial point
        if (x1 > x2){
            qDebug() << "X1 > x2";
            x = x2;
            y = y2;
            if (y < y1)
                incrY = true;
            xEnd = x1;
        }else{
            qDebug() << "X1 < x2";
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
        qDebug() << "Case 2: Slope above 45";
        //Deciding initial point
        if (y1 > y2){
            qDebug() << "Y1 > Y2";
            x = x2;
            y = y2;
            if (x < x1)
                incrX = true;
            yEnd = y1;
        }else{
            qDebug() << "Y1 < Y2";
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
    ui->lbl_draw->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_btn_dda_clicked()
{
    float x1 = ui->txt_x1->text().toFloat();
    float y1 = ui->txt_y1->text().toFloat();
    float x2 = ui->txt_x2->text().toFloat();
    float y2 = ui->txt_y2->text().toFloat();
    drawLineDDA(x1,y1,x2,y2);
}

void MainWindow::on_btn_bresm_clicked()
{
    int x1 = ui->txt_x1->text().toInt();
    int y1 = ui->txt_y1->text().toInt();
    int x2 = ui->txt_x2->text().toInt();
    int y2 = ui->txt_y2->text().toInt();
    drawLineBresenhem(x1,y1,x2,y2);
}

void MainWindow::on_btn_clear_window_clicked()
{
    image = QImage(width,height,QImage::Format_RGB888);
    ui->lbl_draw->clear();
    ui->lbl_draw->setPixmap(QPixmap::fromImage(image));
}
