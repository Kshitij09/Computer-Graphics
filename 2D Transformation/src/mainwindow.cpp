#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtMath>
#include "clickablelabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    width = ui->label->width();
    height = ui->label->height();
    image = QImage(width,height,QImage::Format_RGB888);
    //X-axis
    offsetX = height/2-1;
    drawLineBresenham(0,offsetX,width-1,offsetX,qRgb(255,0,0));
    //Y-axis
    offsetY = width/2-1;
    drawLineBresenham(offsetY,0,offsetY,height-1,qRgb(255,0,0));
    connect(ui->label,SIGNAL(mouse_clicked()),this,SLOT(mouse_clicked()));
    connect(ui->label,SIGNAL(mouse_right_clicked()),this,SLOT(mouse_right_clicked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mouse_clicked()
{
    int x = ui->label->x;
    int y = ui->label->y;
    if (firstClick) {
        x1 = x;
        y1 = y;
        lastX = x;
        lastY = y;
        points.push_back(QPoint(x-offsetX,y-offsetY));
        firstClick = false;
    } else {
        drawLineBresenham(lastX,lastY,x,y);
        points.push_back(QPoint(x-offsetX,y-offsetY));
        lastX = x;
        lastY = y;
    }
}

void MainWindow::mouse_right_clicked()
{
    if (!firstClick) {
        drawLineBresenham(x1,y1,lastX,lastY);
        firstClick = true;
    }
}

void MainWindow::drawLineBresenham(int x1, int y1, int x2, int y2,QRgb color)
{
    //QRgb blue = qRgb(0,0,255);
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x,y,xEnd,yEnd;

    //Decision variable p for determing value of y
    bool incrY = false;
    bool incrX = false;
    int p = 2 * dy - dx;
    if (dx > dy){
        //Slope is below 45 degree, x will always increament and y will depend upon p
        //qDebug() << "Case 1: Slope below 45";
        //Deciding initial point
        if (x1 > x2){
            //qDebug() << "X1 > x2";
            x = x2;
            y = y2;
            if (y < y1)
                incrY = true;
            xEnd = x1;
        }else{
            //qDebug() << "X1 < x2";
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
        //qDebug() << "Case 2: Slope above 45";
        //Deciding initial point
        if (y1 > y2){
            //qDebug() << "Y1 > Y2";
            x = x2;
            y = y2;
            if (x < x1)
                incrX = true;
            yEnd = y1;
        }else{
            //qDebug() << "Y1 < Y2";
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

void MainWindow::on_btn_translate_clicked()
{
    matrix.setPoints(points);
    float tx = ui->txt_tx->text().toFloat();
    float ty = ui->txt_ty->text().toFloat();
    std::vector<QPoint> result = matrix.translate(tx,ty);
    showResult(result);
}

void MainWindow::on_btn_scale_clicked()
{
    matrix.setPoints(points);
    float sx = ui->txt_sx->text().toFloat();
    float sy = ui->txt_sy->text().toFloat();
    std::vector<QPoint> result = matrix.scale(sx,sy);
    showResult(result);
}

void MainWindow::on_btn_rotate_clicked()
{
    QPoint tempX = points.front();
    float theta = ui->txt_theta->text().toFloat();
    std::vector<QPoint> result;
    matrix.setPoints(points);
    //Step 1: Translate to origin
    result = matrix.translate(-tempX.x(),-tempX.y());
    matrix.setPoints(result);
    //Step 2: Rotate
    result = matrix.rotate(theta*M_PI/180);
    matrix.setPoints(result);
    //Step 3: Translate back
    result = matrix.translate(tempX.x(),tempX.y());

    showResult(result);
}

void MainWindow::on_ref_x_clicked()
{
    matrix.setPoints(points);
    std::vector<QPoint> result = matrix.reflectX();
    showResult(result);
}

void MainWindow::on_ref_y_clicked()
{
    matrix.setPoints(points);
    std::vector<QPoint> result = matrix.reflectY();

    showResult(result);
}

void MainWindow::on_ref_yx_clicked()
{
    matrix.setPoints(points);
    std::vector<QPoint> result = matrix.reflectYX();

    showResult(result);
}
void MainWindow::showResult(std::vector<QPoint> result)
{
    QPoint A;
    QPoint B;
    for (int i = 0; i < result.size()-1; ++i) {
        A = result[i];
        B = result[i+1];
        drawLineBresenham(A.x()+offsetX,A.y()+offsetY,B.x()+offsetX,B.y()+offsetY,qRgb(0,255,0));
    }
    A = result[0];
    drawLineBresenham(A.x()+offsetX,A.y()+offsetY,B.x()+offsetX,B.y()+offsetY,qRgb(0,255,0));
}
