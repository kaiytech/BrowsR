#ifndef ADDRESSBAR_H
#define ADDRESSBAR_H

#include <QWidget>
#include <QLineEdit>
#include "mainwindow.h"

class AddressBar : public QLineEdit
{
    Q_OBJECT
public:
    explicit AddressBar(QWidget *parent, MainWindow* mainWindow);
    void UpdateUrl(QString);
    void Fit();

private:
    MainWindow* pMainWindow;

protected:
    //void keyPressEvent(QKeyEvent*);
    bool eventFilter(QObject*, QEvent*);
signals:

};

#endif // ADDRESSBAR_H
