#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clicklabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setMouseTracking(true);
    connect(ui->label,SIGNAL(mouse_pos()),this,SLOT(mouse_pos()));
    connect(ui->label,SIGNAL(mouse_pressed()),this,SLOT(mouse_pressed()));
    connect(ui->label,SIGNAL(mouse_right_clicked()),this,SLOT(mouse_right_clicked()));
    connect(ui->label,SIGNAL(mouse_left()),this,SLOT(mouse_left()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouse_pos()
{
    ui->mouse_cord->setText(QString("X = %1, Y = %2")
                            .arg(ui->label->x)
                            .arg(ui->label->y));
    ui->mouse_eve->setText(QString("Mouse Moving !"));
}

void MainWindow::mouse_pressed()
{
    ui->mouse_eve->setText(QString("Mouse Clicked !"));
}
void MainWindow::mouse_right_clicked()
{
    ui->mouse_eve->setText(QString("Mouse Right Clicked !"));
}

void MainWindow::mouse_left()
{
    ui->mouse_eve->setText(QString("Mouse Left !"));
}
