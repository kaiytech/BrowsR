#include "closebutton.h"
#include "TabManager.h"
#include "browsrexception.h"

CloseButton::CloseButton(QWidget *parent)
    : QWidget{parent}
{
    if (parent == nullptr)
        throw new BrowsRException("Couldn't initialize the Close Button with a null parent.");

    setParent(parent);
    show();
}

void CloseButton::MoveTo(QRect rect, bool addaptive) {
    if (rect.isEmpty() || rect.isNull())
        throw new BrowsRException("Couldn't move the Close Button to an empty or null QRect.");
    if (addaptive)
        setGeometry(rect.x() + rect.width(), rect.y() + 2, rect.height(), rect.height() - 4);
    else
        setGeometry(rect.x(), rect.y() + 2, rect.height(), rect.height() - 4);
    setStyleSheet("background-color:#d9d9d9; border-top: 1px solid #c2c2c2; border-right: 1px solid #c2c2c2;");
    repaint();
    show();
}

void CloseButton::mousePressEvent(QMouseEvent *event) {
    GetTabManager()->NewTab();
    //repaint();
    emit clicked();
}

void CloseButton::paintEvent(QPaintEvent* event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void CloseButton::mouseMoveEvent(QMouseEvent *event) {

}
