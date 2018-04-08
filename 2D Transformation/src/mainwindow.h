#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <transmatrix.h>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage image;
    std::vector<QPoint> points;
    TransMatrix matrix;
    int width;
    int height;
    int offsetX;
    int offsetY;
    bool firstClick;
    int x1,y1;
    int lastX,lastY;
    explicit MainWindow(QWidget *parent = 0);
    void showResult(std::vector<QPoint> result);
    void drawLineBresenham(int x1,int y1,int x2, int y2,QRgb color = qRgb(0,0,255));
    ~MainWindow();

private slots:
    void mouse_clicked();
    void mouse_right_clicked();

    void on_btn_translate_clicked();
    void on_btn_scale_clicked();
    void on_btn_rotate_clicked();
    void on_ref_x_clicked();
    void on_ref_y_clicked();    
    void on_ref_yx_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
