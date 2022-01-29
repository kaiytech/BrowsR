#include "settings.h"
#include <QSettings>
#include <QFile>

Settings *__settings;

Settings *AppSettings() {
    if (__settings == nullptr)
        __settings = new Settings();

    return __settings;
}

Settings::Settings()
{
    QFile file("settings.ini");
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.write("[settings]ExitWhenLastTabClosed=1 NewTab=0 NewTabUrl=http://facebook.com/ HomePageUrl=http://google.com/");
        file.close();
    }

    QSettings settings(QString("settings.ini"), QSettings::IniFormat);
    bool ewltc = settings.value("settings/ExitWhenLastTabClosed", "true").toBool();

    NewTabBehaviour ntb;
    auto ntb_s = settings.value("settings/NewTab", "0").toString();
    if (ntb_s.compare("0")) {
        ntb = NewTabBehaviour::BLANK_PAGE;
    } else if (ntb_s.compare("1")) {
        ntb = NewTabBehaviour::HOME_PAGE;
    } else {
        ntb = NewTabBehaviour::CUSTOM_URL;
    }

    QString ntu = settings.value("settings/NewTabUrl", "http://facebook.com/").toString();
    QString hpu = settings.value("settings/HomePageUrl", "http://google.com/").toString();

    Update(ewltc, ntb, ntu, hpu);
}

void Settings::Update(bool ExitWhenLastTabClosed, NewTabBehaviour NewTabBehaviour, QString NewTabUrl, QString HomePageUrl) {
    bExitWhenLastTabClosed = ExitWhenLastTabClosed;
    eNewTabBehaviour = NewTabBehaviour;
    sNewTabUrl = NewTabUrl;
    sHomePageUrl = HomePageUrl;

    QSettings settings(QString("settings.ini"), QSettings::IniFormat);
    settings.setValue("settings/ExitWhenLastTabClosed", bExitWhenLastTabClosed);
    settings.setValue("settings/NewTabUrl", sNewTabUrl);
    settings.setValue("settings/HomePageUrl", sHomePageUrl);

    switch (eNewTabBehaviour) {
        case BLANK_PAGE:
            settings.setValue("settings/NewTab", "0");
            break;
        case HOME_PAGE:
            settings.setValue("settings/NewTab", "1");
            break;
        case CUSTOM_URL:
            settings.setValue("settings/NewTab", "2");
            break;
    }
}

bool Settings::Get_ExitWhenLastTabClosed() {
    return bExitWhenLastTabClosed;
}

NewTabBehaviour Settings::Get_NewTabBehaviour() {
    return eNewTabBehaviour;
}

QString Settings::Get_NewTabUrl() {
    return sNewTabUrl;
}

QString Settings::Get_HomePageUrl() {
    return sHomePageUrl;
}
