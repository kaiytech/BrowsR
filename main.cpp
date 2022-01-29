#include "mainwindow.h"
#include "TabManager.h"
#include "settings.h"
#include "browsrexception.h"

#include <QApplication>

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);

        MainWindow *w = new MainWindow();
        w->show();

        AppSettings();

        int r = a.exec();
        return r;
}
