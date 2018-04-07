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
    int width,height;
    QImage image;
    explicit MainWindow(QWidget *parent = 0);
    void drawLineDDA(float x1, float y1,float x2, float y2);
    void drawLineBresenhem(int x1, int y1,int x2, int y2);
    ~MainWindow();

private slots:
    void on_btn_dda_clicked();

    void on_btn_bresm_clicked();

    void on_btn_clear_window_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
