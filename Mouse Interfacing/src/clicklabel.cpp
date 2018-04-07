#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget* parent):
    QLabel(parent)
{

}

void ClickLabel::mouseMoveEvent(QMouseEvent *event)
{
    this->x = event->x();
    this->y = event->y();
    emit mouse_pos();
}

void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        emit mouse_right_clicked();
    else
        emit mouse_pressed();
}

void ClickLabel::leaveEvent(QEvent *event)
{
    emit mouse_left();
}
