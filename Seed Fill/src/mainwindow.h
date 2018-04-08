#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clicklabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage image;
    QRgb color;
    QColor bgcolor;
    int width,height;
    bool firstClick;
    bool polyCompleted;
    int x1,y1;
    int lastX,lastY;
    explicit MainWindow(QWidget *parent = 0);
    void floodFill(int x,int y,QRgb newColor);
    void drawLineBresenhem(int x1, int y1, int x2, int y2);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void mouse_clicked();
    void on_btn_fill_clicked();
};

#endif // MAINWINDOW_H
