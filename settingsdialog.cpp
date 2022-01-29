#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"
#include <QSysInfo>
#include <QProcess>
#include <QStandardPaths>


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowTitle("Settings - BrowsR");

    ui->settingsExitWhenLastTabClosed->setChecked(AppSettings()->Get_ExitWhenLastTabClosed());
    ui->settingsNewTabURL->setText(AppSettings()->Get_NewTabUrl());
    ui->settingsHomePageURL->setText(AppSettings()->Get_HomePageUrl());

    ui->settingsNewTabBlankPage->setChecked(false);
    ui->settingsNewTabHomePage->setChecked(false);
    ui->settingsNewTabURLPage->setChecked(false);
    ui->browseDownloadsButton->hide();

    switch (AppSettings()->Get_NewTabBehaviour()) {
        case BLANK_PAGE:
            ui->settingsNewTabBlankPage->setChecked(true);
            ui->settingsNewTabURL->setDisabled(true);
            break;
        case HOME_PAGE:
            ui->settingsNewTabHomePage->setChecked(true);
            ui->settingsNewTabURL->setDisabled(true);
            break;
        case CUSTOM_URL:
            ui->settingsNewTabURLPage->setChecked(true);
            ui->settingsNewTabURL->setDisabled(false);
            break;
    }


}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    NewTabBehaviour ntb;
    if (ui->settingsNewTabBlankPage->isChecked())       ntb = NewTabBehaviour::BLANK_PAGE;
    else if (ui->settingsNewTabHomePage->isChecked())   ntb = NewTabBehaviour::HOME_PAGE;
    else                                                ntb = NewTabBehaviour::CUSTOM_URL;

    AppSettings()->Update(ui->settingsExitWhenLastTabClosed->isChecked(), ntb, ui->settingsNewTabURL->text(), ui->settingsHomePageURL->text());
}


void SettingsDialog::on_buttonBox_rejected()
{

}


void SettingsDialog::on_settingsNewTabURLPage_toggled(bool checked)
{
    ui->settingsNewTabURL->setDisabled(!checked);
}


void SettingsDialog::on_browseDownloadsButton_pressed()
{

    if (QSysInfo::productType().compare("winrt")) {
        QProcess *process = new QProcess(this);
        QStringList arguments;
        arguments << QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        process->startDetached("explorer.exe", arguments);
        delete process;
    } else if (QSysInfo::productType().compare("osx")) {
        QProcess *process = new QProcess(this);
        process->startDetached("tell application \"Finder\" to reveal POSIX file \""+QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)+"\"");
        delete process;
    } else {
        QProcess *process = new QProcess(this);
        QStringList arguments;
        arguments << QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        process->startDetached("thunar", arguments);
        delete process;
    }
}

