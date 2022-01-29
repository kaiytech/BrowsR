#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QMainWindow>
#include <QWebEngineView>

class Tab {
public:
    Tab(QWidget*, bool);
    ~Tab();

    void NavigateTo(QString url);

    void ResizeToFit();
    QWidget *GetParentWidget();

    QString GetCurrentUrl();


    bool CanGoBack();
    bool CanGoForwards();

    void GoBack();
    void GoForwards();



private:
    QWebEngineView* pEngine;
    QWidget *pWidget;

    void titleChanged(const QString &title);
    void iconChanged(const QIcon &icon);

    bool bInFocus;
};

#endif // TAB_H
