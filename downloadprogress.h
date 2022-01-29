#ifndef DOWNLOADPROGRESS_H
#define DOWNLOADPROGRESS_H

#include <QDialog>
#include <QWebEngineDownloadRequest>

namespace Ui {
class downloadprogress;
}

class downloadprogress : public QDialog
{
    Q_OBJECT

public:
    explicit downloadprogress(QWidget *parent = nullptr);
    ~downloadprogress();
    void populate(QWebEngineDownloadRequest *download);

private:
    Ui::downloadprogress *ui;
    QWebEngineDownloadRequest *download;
};

#endif // DOWNLOADPROGRESS_H
