#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include "Tab.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

private slots:
    void on_tabSwitcher_tabBarClicked(int index);
    void on_tabSwitcher_currentChanged(int index);
    void on_tabSwitcher_tabCloseRequested(int index);
    void on_settingsButton_clicked();
    void on_backButtonNav_clicked();
    void on_forwardsButtonNav_clicked();

private:
    Tab *activeTab;

    void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
