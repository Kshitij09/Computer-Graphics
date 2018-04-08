#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    width = ui->label->width();
    height = ui->label->height();
    image = QImage(width,height,QImage::Format_RGB888);
    newImage = QImage(width,height,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image));
    connect(ui->label,SIGNAL(mouse_clicked()),this,SLOT(mouse_clicked()));
    connect(ui->label,SIGNAL(mouse_position()),this,SLOT(mouse_position()));
    connect(ui->label,SIGNAL(mouse_released()),this,SLOT(mouse_released()));
    firstClick = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouse_position()
{

}

void MainWindow::mouse_clicked()
{
    this->x = ui->label->x;
    this->y = ui->label->y;
    QPoint point(x,y);
    if (ui->rb_line->isChecked()) {
        if (firstClick) {
            x1 = x;
            y1 = y;
            points.push_back(point);
            firstClick = false;
        } else {
            drawLineBresenham(x1,y1,x,y);
            points.push_back(point);
            firstClick = true;
        }
    }
}

void MainWindow::mouse_released()
{
    if (ui->rb_window->isChecked())
        drawRectangle(x,y,ui->label->relX,ui->label->relY);
}



void MainWindow::drawRectangle(int x1, int y1, int x2, int y2)
{
    //qDebug() << "X1 = " << x1 << " Y1 = " << y1;
    //qDebug() << "X2 = " << x2 << " Y2 = " << y2;
    //Initiating window co-ordinates
    xL = x1;
    yL = y2;
    xH = x2;
    yH = y1;

    QRgb blue = qRgb(255,0,0);
    drawLineBresenham(x1,y1,x2,y1,blue);
    drawLineBresenham(x2,y1,x2,y2,blue);
    drawLineBresenham(x1,y2,x2,y2,blue);
    drawLineBresenham(x1,y1,x1,y2,blue);
}

int *MainWindow::getOutcode(QPoint point)
{
    int* outcode = new int[4];
    //Left edge
    outcode[3] = (point.x() < xL) ? 1 : 0;
    outcode[2] = (point.x() > xH) ? 1 : 0;
    /*conditions for y co-ordinates will change
     * as we're working in 4th quadrant
     */
    outcode[1] = (point.y() > yL) ? 1 : 0;
    outcode[0] = (point.y() < yH) ? 1 : 0;

    return outcode;
}


int MainWindow::case_test(int *oc1, int *oc2)
{
    int i;
    bool nonZero=false;
    bool allZero=true;
    //Checking whether both outcodes are zero
    for (i = 0; i < 4; ++i) {
        if ((oc1[i] & oc2[i])){
            nonZero = true;
        }
        if (oc1[i] || oc2[i])
            allZero = false;
    }
    if (allZero)
        return 0;
    if (nonZero)
        return 1;
    else
        return 2;
}

void MainWindow::on_btn_clip_clicked()
{
    QPoint A,B;         //Endpoints
    int* ocA,*ocB;      //Outcodes
    int i;

    //no. of points should be greater than 2 for clipping
    if ((points.size() >= 2)) {
        image = newImage;
        drawRectangle(xL,yH,xH,yL);
        for (int x = 0; x < points.size()-1; x+=2) {
            A = points[x];
            B = points[x+1];
            //Getting outcode
            ocA = getOutcode(A);
            ocB = getOutcode(B);
            //Checking for case of line
            int c = case_test(ocA,ocB);
            switch (c) {
                case 0:
                    //Completely visible
                    drawLineBresenham(A.x(),A.y(),B.x(),B.y());
                    break;
                case 1:
                    //Completely invisible
                    break;
                case 2:
                    /*Cannot be determined, need to go
                     * one step further
                     */
                    for (i = 3; i >= 0; i--) {
                        // Both bits are zero, continue with next iteration
                        if (ocA[i] == 0 && ocB[i] == 0)
                            continue;
                        else if (ocA[i] == 1)
                            A = getIntersect(A,B,i);
                        else
                            B = getIntersect(B,A,i);

                    }
                    drawLineBresenham(A.x(),A.y(),B.x(),B.y());
                    break;
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
}

QPoint MainWindow::getIntersect(QPoint A, QPoint B, int i)
{
    float m = (B.y()-A.y()) / (B.x()-A.x());    //slope
    QPoint inter;
    switch (i) {
        case 3:
            inter.setX(xL);
            inter.setY(A.y() + (m*(xL - A.x())));
        break;

        case 2:
            inter.setX(xH);
            inter.setY(A.y() + (m*(xH - A.x())));
        break;

        case 1:
            inter.setY(yL);
            inter.setX(A.x() + ((yL - A.y())/m));
        break;

        case 0:
            inter.setY(yH);
            inter.setX(A.x() + ((yH - A.y())/m));
        break;
    }
    return inter;
}
void MainWindow::drawLineBresenham(int x1, int y1, int x2, int y2,QRgb color){
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
