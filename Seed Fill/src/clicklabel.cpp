#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent) : QLabel(parent)
{

}

void ClickLabel::mousePressEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    isRight = ev->button() == Qt::RightButton;
    emit mouse_clicked();
}
