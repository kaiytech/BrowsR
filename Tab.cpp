#include "Tab.h"
#include <QFrame>
#include "TabManager.h"
#include "settings.h"
#include "browsrexception.h"
#include <QWebEngineDownloadRequest>
#include "downloadmanager.h"

Tab::Tab(QWidget* widget, bool homePage) {
    if (widget == nullptr)
        throw new BrowsRException("Couldn't create new tab. The parent QWidget was null.");

    pWidget = widget;

    pWidget->move(0, 0);
    pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //pWidget->show();

    pEngine = new QWebEngineView(pWidget);

    if (!pEngine)
        throw new BrowsRException("Failed to initialize WebEngineView.");

    if (homePage) {
        pEngine->load(AppSettings()->Get_HomePageUrl());
    }
    else {
        switch (AppSettings()->Get_NewTabBehaviour()) {
            case BLANK_PAGE:
                pEngine->setContent("");
                break;
            case HOME_PAGE:
                pEngine->load(AppSettings()->Get_HomePageUrl());
                break;
            case CUSTOM_URL:
                pEngine->load(AppSettings()->Get_NewTabUrl());
                break;
        }
    }


    QObject::connect(pEngine, &QWebEngineView::titleChanged, [this](const QString &title) {
            titleChanged(title);
        });

    QObject::connect(pEngine, &QWebEngineView::iconChanged, [this](const QIcon &icon) {
            iconChanged(icon);
        });

    QObject::connect(pEngine, &QWebEngineView::urlChanged, [this](const QUrl url) {
            GetTabManager()->UpdateUrl(this, url.toString());
    });

    QObject::connect(pEngine->page()->profile(), &QWebEngineProfile::downloadRequested, [this](QWebEngineDownloadRequest *download) {
            GetDownloadManager()->RequestDownload(download);
    });

    pEngine->show();
}

void Tab::NavigateTo(QString url) {
    pEngine->load(QUrl(url));
}

void Tab::ResizeToFit() {
    pEngine->resize(pWidget->width(), pWidget->height());
}

QWidget* Tab::GetParentWidget() {
    return pWidget;
}

QString Tab::GetCurrentUrl() {
    return pEngine->url().toString();
}

void Tab::titleChanged(const QString &title) {
    GetTabManager()->UpdateTitle(this, title);
}

void Tab::iconChanged(const QIcon &icon) {
    GetTabManager()->UpdateIcon(this, icon);
}

void Tab::GoBack() {
    pEngine->back();
}

void Tab::GoForwards() {
    pEngine->forward();
}

bool Tab::CanGoBack() {
    return pEngine->history()->canGoBack();
}

bool Tab::CanGoForwards() {
    return pEngine->history()->canGoForward();
}

Tab::~Tab() {
    delete pWidget;
    delete pEngine;
}
