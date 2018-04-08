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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage image;
    void drawLineDDA(float x1, float y1, float x2, float y2);
    void drawLineDotted(float x1, float y1, float x2, float y2);
    void drawLineDashed(float x1, float y1, float x2, float y2);
    void drawLineDashDotted(float x1, float y1, float x2, float y2);
    void drawThickLine(float x1, float y1, float x2, float y2, float wt);
private slots:
    void on_btn_solid_clicked();

    void on_btn_dotted_clicked();

    void on_btn_dash_clicked();

    void on_btn_dash_dot_clicked();

    void on_btn_thick_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
