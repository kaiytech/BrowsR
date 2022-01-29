#ifndef DOWNLOADSDIALOG_H
#define DOWNLOADSDIALOG_H

#include <QDialog>

namespace Ui {
class DownloadsDialog;
}

class DownloadsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadsDialog(QWidget *parent = nullptr);
    ~DownloadsDialog();

private slots:
    void on_DownloadsDialog_accepted();

private:
    Ui::DownloadsDialog *ui;
};

#endif // DOWNLOADSDIALOG_H
