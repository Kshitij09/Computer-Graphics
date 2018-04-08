#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent) : QLabel(parent)
{

}

void ClickLabel::mouseMoveEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    emit mouse_position();
}

void ClickLabel::mousePressEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    emit mouse_clicked();
}

void ClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    this->relX = ev->x();
    this->relY = ev->y();
    emit mouse_released();
}
