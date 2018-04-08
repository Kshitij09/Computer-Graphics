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

void MainWindow::drawLineDotted(float x1, float y1, float x2, float y2){
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
        if (int(X)%2 == 1)
            image.setPixel(X,Y,red);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::drawLineDashed(float x1, float y1, float x2, float y2){
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
        if (int(X)%15 <= 7)
            image.setPixel(X,Y,red);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::drawLineDashDotted(float x1, float y1, float x2, float y2){
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
        if ((int(X)%18 <= 8) || (int(X)%18 == 13))
            image.setPixel(X,Y,red);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::drawThickLine(float x1, float y1, float x2, float y2, float wt){
    QRgb red;
    red = qRgb(255,0,0);

    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);
    float w = ((wt-1)/2) * sqrt((dx*dx) + (dy*dy)) / length;
    float xInc = dx / length;
    float yInc = dy / length;

    float X = x1;
    float Y = y1;
    image.setPixel(X,Y,red);
    for (int i=1; i <= length; i++){
        for (int j=0; j < w; j++){
            if (abs(dx) > abs(dy)){
                image.setPixel(X,Y+j,red);
                image.setPixel(X,Y-j,red);
            }else{
                image.setPixel(X+j,Y,red);
                image.setPixel(X-j,Y,red);
            }
        }
        X += xInc;
        Y += yInc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_btn_solid_clicked()
{
    float x1 = ui->txt_X1->text().toFloat();
    float y1 = ui->txt_Y1->text().toFloat();
    float x2 = ui->txt_X2->text().toFloat();
    float y2 = ui->txt_Y2->text().toFloat();
    drawLineDDA(x1,y1,x2,y2);
}

void MainWindow::on_btn_dotted_clicked()
{
    float x1 = ui->txt_X1->text().toFloat();
    float y1 = ui->txt_Y1->text().toFloat();
    float x2 = ui->txt_X2->text().toFloat();
    float y2 = ui->txt_Y2->text().toFloat();
    drawLineDotted(x1,y1,x2,y2);
}

void MainWindow::on_btn_dash_clicked()
{
    float x1 = ui->txt_X1->text().toFloat();
    float y1 = ui->txt_Y1->text().toFloat();
    float x2 = ui->txt_X2->text().toFloat();
    float y2 = ui->txt_Y2->text().toFloat();
    drawLineDashed(x1,y1,x2,y2);
}

void MainWindow::on_btn_dash_dot_clicked()
{
    float x1 = ui->txt_X1->text().toFloat();
    float y1 = ui->txt_Y1->text().toFloat();
    float x2 = ui->txt_X2->text().toFloat();
    float y2 = ui->txt_Y2->text().toFloat();
    drawLineDashDotted(x1,y1,x2,y2);
}

void MainWindow::on_btn_thick_clicked()
{
    float x1 = ui->txt_X1->text().toFloat();
    float y1 = ui->txt_Y1->text().toFloat();
    float x2 = ui->txt_X2->text().toFloat();
    float y2 = ui->txt_Y2->text().toFloat();
    float w = ui->txt_thick->text().toFloat();
    drawThickLine(x1,y1,x2,y2,w);
}
