#include "addressbar.h"
#include <QWidget>
#include "mainwindow.h"
#include "TabManager.h"
#include "browsrexception.h"

AddressBar::AddressBar(QWidget *parent, MainWindow* mainWindow)
    : QLineEdit{parent}
{
    if (mainWindow == nullptr)
        throw new BrowsRException("Couldn't initialize the Address Bar with null MainWindow.");
    pMainWindow = mainWindow;
    qApp->installEventFilter(this);
    Fit();
    setMouseTracking(true);
}

void AddressBar::UpdateUrl(QString text) {
    setText(text);
    Fit();
}

void AddressBar::Fit() {
    //10, 10, 23
    show();
    move(52,10);
    resize(parentWidget()->width() - 20 - 40 - 30, 23);
}

bool AddressBar::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if (key->key() == 16777220)
            GetTabManager()->NavigateTo(text());
    }
    return QObject::eventFilter(obj, event);
}

/*void AddressBar::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter) {
        GetTabManager()->NavigateTo(text());
    } else {

    }

}*/
