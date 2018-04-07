#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    int x,y;
    ClickLabel(QWidget* parent);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void leaveEvent(QEvent* event);
signals:
    void mouse_pos();
    void mouse_pressed();
    void mouse_released();
    void mouse_right_clicked();
    void mouse_left();
};

#endif // CLICKLABEL_H
