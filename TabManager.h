#ifndef TABMANAGER_H
#define TABMANAGER_H

#include "Tab.h"
#include <QFrame>
#include <stdlib.h>
#include "mainwindow.h"
#include "closebutton.h"
#include "addressbar.h"

class TabManager {
public:
    TabManager();
    ~TabManager();
    void Init(MainWindow*);

    Tab* NewTab(bool homePage = false);
    Tab* GetActiveTab();
    void ResizeToFit();
    void UpdateTitle(Tab*, QString);
    void UpdateIcon(Tab*, QIcon);
    void UpdateUrl(Tab*, QString);
    void UpdateUrl(QString);
    void NavigateTo(QString);
    void CloseTab(int);
    void GoBack();
    void GoForwards();

private:
    QVector<Tab*> vTabs;
    QTabWidget* pTabWidget;
    AddressBar* pAddressBar;

    QPushButton* pButtonBack;
    QPushButton* pButtonForwards;

    CloseButton* pCloseButton;

    void UpdateCloseButtonPosition();
    void UpdateNavigationButtons();
};

TabManager* GetTabManager();

#endif // TABMANAGER_H
