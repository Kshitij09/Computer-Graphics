#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage image;
    QRgb red = qRgb(255,0,0);
    QRgb blue = qRgb(0,0,255);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void circBresenham(int xc,int yc,int r);
    void drawCircle(int xc,int yc,int x,int y);
    void circDDA(int xc,int yc,int r);

private slots:
    void on_btn_bresenham_clicked();

    void on_btn_dda_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
