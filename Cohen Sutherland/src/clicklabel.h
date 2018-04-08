#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <Qt>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    int x,y;
    int relX,relY;
    explicit ClickLabel(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
signals:
    void mouse_position();
    void mouse_clicked();
    void mouse_released();
};

#endif // CLICKLABEL_H
