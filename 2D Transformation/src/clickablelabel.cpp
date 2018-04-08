#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent) :
    QLabel(parent)
{

}

void ClickableLabel::mousePressEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    if (ev->button() == Qt::RightButton)
        emit mouse_right_clicked();
    else
        emit mouse_clicked();
}
