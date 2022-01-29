QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Tab.cpp \
    TabManager.cpp \
    addressbar.cpp \
    browsrexception.cpp \
    closebutton.cpp \
    downloadmanager.cpp \
    downloadprogress.cpp \
    downloadprompt.cpp \
    downloadsdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    settingsdialog.cpp

HEADERS += \
    Tab.h \
    TabManager.h \
    addressbar.h \
    browsrexception.h \
    closebutton.h \
    downloadmanager.h \
    downloadprogress.h \
    downloadprompt.h \
    downloadsdialog.h \
    mainwindow.h \
    settings.h \
    settingsdialog.h

FORMS += \
    downloadprogress.ui \
    downloadprompt.ui \
    downloadsdialog.ui \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
