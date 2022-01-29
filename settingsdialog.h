#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_settingsNewTabURLPage_toggled(bool checked);

    void on_browseDownloadsButton_pressed();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
