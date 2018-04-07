#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = QImage(ui->label_draw->width(),
                   ui->label_draw->height(),
                   QImage::Format_RGB888);
    ui->label_draw->setPixmap(QPixmap::fromImage(image));
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
    image.setPixel(xc+x,yc+y,red);
    image.setPixel(xc-x,yc+y,red);
    image.setPixel(xc+x,yc-y,red);
    image.setPixel(xc-x,yc-y,red);
    image.setPixel(xc+y,yc+x,red);
    image.setPixel(xc-y,yc+x,red);
    image.setPixel(xc+y,yc-x,red);
    image.setPixel(xc-y,yc-x,red);
    ui->label_draw->setPixmap(QPixmap::fromImage(image));
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
        image.setPixel(xc+xc2,yc-yc2,blue);
        xc1 = xc2;
        yc1 = yc2;
    } while((yc1-sy)<eps || (sx-xc1)>eps);
    ui->label_draw->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_btn_bresenham_clicked()
{
    int x = ui->txtX->text().toInt();
    int y = ui->txtY->text().toInt();
    int radius = ui->txtRadius->text().toInt();
    circBresenham(x,y,radius);
}

void MainWindow::on_btn_dda_clicked()
{
    int x = ui->txtX->text().toInt();
    int y = ui->txtY->text().toInt();
    int radius = ui->txtRadius->text().toInt();
    circDDA(x,y,radius);
}
