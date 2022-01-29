#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QWidget>

class CloseButton : public QWidget
{
    Q_OBJECT
public:
    explicit CloseButton(QWidget *parent = nullptr);
    void MoveTo(QRect, bool addaptive = true);

protected:
    void mousePressEvent(QMouseEvent*);
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void clicked();

};

#endif // CLOSEBUTTON_H
