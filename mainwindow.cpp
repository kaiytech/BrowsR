#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tab.h"
#include "TabManager.h"
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QUrl>
#include "settingsdialog.h"
#include "browsrexception.h"

#include "downloadsdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->settingsButton->setIcon(QIcon("settings.png"));
    ui->backButtonNav->setIcon(QIcon("aleft.png"));
    ui->forwardsButtonNav->setIcon(QIcon("aright.png"));
    GetTabManager()->Init(this);
    statusBar()->hide();

    GetTabManager()->NewTab(true);
    GetTabManager()->ResizeToFit();
    connect(ui->settingsButton, SIGNAL(QPushButton::clicked()), this, SLOT(on_settingsButton_clicked()));
    connect(ui->backButtonNav, SIGNAL(QPushButton::clicked()), this, SLOT(on_backButtonNav_clicked()));
    connect(ui->forwardsButtonNav, SIGNAL(QPushButton::clicked()), this, SLOT(on_forwardsButtonNav_clicked()));
    showMaximized();

    //DownloadsDialog d;
    //d.exec();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    ui->tabSwitcher->resize(this->width(), this->height() - 60);
    ui->settingsButton->move(this->width() - 30, ui->settingsButton->y());
    GetTabManager()->ResizeToFit();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabSwitcher_tabBarClicked(int index)
{
    GetTabManager()->ResizeToFit();
    setWindowTitle("" + ui->tabSwitcher->tabText(index) + " - BrowsR");
}

void MainWindow::on_tabSwitcher_currentChanged(int index)
{
    GetTabManager()->ResizeToFit();
    setWindowTitle("" + ui->tabSwitcher->tabText(index) + " - BrowsR");
}

void MainWindow::on_tabSwitcher_tabCloseRequested(int index) {
    GetTabManager()->CloseTab(index);
}

void MainWindow::on_settingsButton_clicked() {
    SettingsDialog s;
    s.exec();
}

void MainWindow::on_backButtonNav_clicked() {
    GetTabManager()->GoBack();
}

void MainWindow::on_forwardsButtonNav_clicked() {
    GetTabManager()->GoForwards();
}


