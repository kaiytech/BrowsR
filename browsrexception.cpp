#include "browsrexception.h"
#include <QMessageBox>
#include <QApplication>

BrowsRException::BrowsRException(QString msg)
{
    sMsg = msg;
    QMessageBox error1;
    error1.critical(0, "Fatal error", "An internal error has occured and BrowsR had to be terminated.\n\n" + msg);
    error1.setFixedSize(700, 200);
    qApp->exit(EXIT_FAILURE);
}

QString BrowsRException::Message() {
    return sMsg;
}
