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

private slots:
    void mouse_pos();
    void mouse_pressed();
    void mouse_released();
    void mouse_right_clicked();
    void mouse_left();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
