#ifndef DOWNLOADPROMPT_H
#define DOWNLOADPROMPT_H

#include <QDialog>
#include <QWebEngineDownloadRequest>

namespace Ui {
class downloadprompt;
}

class downloadprompt : public QDialog
{
    Q_OBJECT

public:
    explicit downloadprompt(QWidget *parent = nullptr);
    ~downloadprompt();
    void populate(QWebEngineDownloadRequest *download);

private slots:
    void on_browse_pressed();

    void on_buttonBox_accepted();

private:
    Ui::downloadprompt *ui;
    QWebEngineDownloadRequest *download;
};

#endif // DOWNLOADPROMPT_H
