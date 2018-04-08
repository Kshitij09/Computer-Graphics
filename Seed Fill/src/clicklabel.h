#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <Qt>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    int x,y;
    bool isRight;
    explicit ClickLabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);
signals:
    void mouse_position();
    void mouse_clicked();
};

#endif // CLICKLABEL_H
