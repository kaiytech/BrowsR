#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

enum NewTabBehaviour {
    BLANK_PAGE,
    HOME_PAGE,
    CUSTOM_URL
};

class Settings
{
public:
    Settings();

    bool Get_ExitWhenLastTabClosed();
    NewTabBehaviour Get_NewTabBehaviour();
    QString Get_NewTabUrl();
    QString Get_HomePageUrl();

    void Update(bool ExitWhenLastTabClosed, NewTabBehaviour NewTabBehaviour, QString NewTabUrl, QString HomePageUrl);

private:
    bool bExitWhenLastTabClosed;
    NewTabBehaviour eNewTabBehaviour;
    QString sNewTabUrl;
    QString sHomePageUrl;
};

Settings* AppSettings();

#endif // SETTINGS_H
