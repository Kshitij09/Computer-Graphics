#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    int x,y;
    ClickableLabel(QWidget* parent);
    void mousePressEvent(QMouseEvent* event);
signals:
    void mouse_position();
    void mouse_clicked();
    void mouse_right_clicked();
};

#endif // CLICKABLELABEL_H
