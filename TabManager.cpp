#include "TabManager.h"
#include <QWidget>
#include <QTabBar>
#include "ui_mainwindow.h"
#include "settings.h"
#include "browsrexception.h"

TabManager *__tabManager;

TabManager *GetTabManager() {
    if (__tabManager == nullptr)
        __tabManager = new TabManager();

    return __tabManager;
}

TabManager::TabManager() {

}

void TabManager::Init(MainWindow* mainWindow) {
    if (mainWindow == nullptr)
        throw new BrowsRException("Couldn't initialize TabManager with null MainWindow.");

    pTabWidget = mainWindow->ui->tabSwitcher;
    pButtonBack = mainWindow->ui->backButtonNav;
    pButtonForwards = mainWindow->ui->forwardsButtonNav;

    pAddressBar = new AddressBar(mainWindow->ui->centralwidget, mainWindow);

    pTabWidget->setMovable(true);
    pTabWidget->setTabsClosable(true);
    auto tempWidget = new QWidget();
    pTabWidget->addTab(tempWidget, "");
    int height = pTabWidget->tabBar()->tabRect(0).height();
    pTabWidget->removeTab(0);
    delete tempWidget;

    pCloseButton = new CloseButton(pTabWidget);
}

Tab *TabManager::NewTab(bool homePage) {
    QWidget *widget = new QWidget();
    widget->resize(pTabWidget->width(), pTabWidget->height());
    Tab *tab = new Tab(widget, homePage);
    pTabWidget->addTab(widget, "New Tab");
    widget->show();
    pTabWidget->setCurrentWidget(widget);
    vTabs.append(tab);
    ResizeToFit();
    UpdateCloseButtonPosition();
    UpdateNavigationButtons();
}

void TabManager::NavigateTo(QString url) {
    if (!url.contains("http://") && !url.contains("https://"))
        url = "http://" + url;
    auto widget = pTabWidget->currentWidget();

    for (int i = 0; i < vTabs.size(); i++)
        if (vTabs[i]->GetParentWidget() == widget)
            vTabs[i]->NavigateTo(url);
    UpdateNavigationButtons();
}

Tab *TabManager::GetActiveTab() {
    return vTabs[pTabWidget->currentIndex()];
}

void TabManager::UpdateTitle(Tab *tab, QString title) {
    int index = pTabWidget->indexOf(tab->GetParentWidget());
    if (index != -1)
        pTabWidget->setTabText(index, title);
    UpdateCloseButtonPosition();
    ResizeToFit();
}

void TabManager::UpdateIcon(Tab *tab, QIcon icon) {
    int index = pTabWidget->indexOf(tab->GetParentWidget());
    // an additional nullcheck is required to prevent the flickering icon
    if (icon.isNull())
        return;
    if (index != -1)
        pTabWidget->setTabIcon(index, icon);
    UpdateCloseButtonPosition();
}

void TabManager::UpdateUrl(Tab *tab, QString url) {
    if (pTabWidget->currentIndex() == pTabWidget->indexOf(tab->GetParentWidget()))
        UpdateUrl(url);
    UpdateNavigationButtons();
}

void TabManager::UpdateUrl(QString url) {
    pAddressBar->UpdateUrl(url);
}

void TabManager::ResizeToFit() {
    auto parent = pTabWidget->parentWidget();
    if (!parent)
        throw new BrowsRException("The parent widget of TabManager has been unexpectibly deleted.");

    pTabWidget->resize(parent->width(), parent->height());
    pAddressBar->Fit();

    for (int i = 0; i < vTabs.size(); i++)
        if (pTabWidget->indexOf(vTabs[i]->GetParentWidget()) == pTabWidget->currentIndex())
            pAddressBar->UpdateUrl(vTabs[i]->GetCurrentUrl());

    for (int i = 0; i < vTabs.size(); i++)
        vTabs[i]->ResizeToFit();

   UpdateNavigationButtons();
}

void TabManager::CloseTab(int index) {
    //pTabWidget->setTabEnabled(index, !pTabWidget->isEnabled());
    pTabWidget->removeTab(index);
    if (pTabWidget->count() == 0 && AppSettings()->Get_ExitWhenLastTabClosed())
        qApp->exit(EXIT_SUCCESS);
    UpdateCloseButtonPosition();
    UpdateNavigationButtons();
}

void TabManager::UpdateCloseButtonPosition() {
    if (pTabWidget->count() > 0) {
        QRect tab = pTabWidget->tabBar()->tabRect(pTabWidget->count() - 1);
        if (tab.isNull() || tab.isEmpty())
            throw new BrowsRException("An unknown error related to the TabWidget has occured.");
        pCloseButton->MoveTo(tab);
        pAddressBar->show();
    }
    else {
        pCloseButton->MoveTo(QRect(0, 0, 35, 35), false);
        pAddressBar->hide();
    }
}

void TabManager::UpdateNavigationButtons() {
    for (int i = 0; i < vTabs.size(); i++)
        if (pTabWidget->indexOf(vTabs[i]->GetParentWidget()) == pTabWidget->currentIndex()) {
            pButtonBack->setEnabled(vTabs[i]->CanGoBack());
            pButtonForwards->setEnabled(vTabs[i]->CanGoForwards());
            break;
        }

}

TabManager::~TabManager() {
    while (vTabs.count() != 0)
        vTabs.removeFirst();
}

void TabManager::GoBack() {
    for (int i = 0; i < vTabs.size(); i++)
        if (pTabWidget->indexOf(vTabs[i]->GetParentWidget()) == pTabWidget->currentIndex())
            vTabs[i]->GoBack();
}

void TabManager::GoForwards() {
    for (int i = 0; i < vTabs.size(); i++)
        if (pTabWidget->indexOf(vTabs[i]->GetParentWidget()) == pTabWidget->currentIndex())
            vTabs[i]->GoForwards();
}
