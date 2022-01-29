#include "downloadprogress.h"
#include "ui_downloadprogress.h"
#include <QNetworkAccessManager>

downloadprogress::downloadprogress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadprogress)
{
    ui->setupUi(this);
    setWindowTitle("Downloading...");
}

void downloadprogress::populate(QWebEngineDownloadRequest *downloadp) {
    download = downloadp;
    ui->fileName->setText(download->downloadFileName());
    download->accept();
}

downloadprogress::~downloadprogress()
{
    delete ui;
}
