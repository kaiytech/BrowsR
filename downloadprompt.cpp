#include "downloadprompt.h"
#include "ui_downloadprompt.h"
#include <QFileDialog>
#include <QMessageBox>

downloadprompt::downloadprompt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadprompt)
{
    ui->setupUi(this);
    setWindowTitle("Download Request");
}

void downloadprompt::populate(QWebEngineDownloadRequest *downloadp) {
    download = downloadp;
    ui->fileName->setText(download->downloadFileName());
    ui->url->setText(download->url().toString());
    ui->path->setText(download->downloadDirectory());
}

downloadprompt::~downloadprompt()
{
    delete ui;
}

void downloadprompt::on_browse_pressed()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setFileMode(QFileDialog::FileMode::AnyFile);
    fd.setDirectory(ui->path->text());
    fd.exec();

    ui->path->setText(fd.directory().path());
}


void downloadprompt::on_buttonBox_accepted()
{
    auto d = new QDir(ui->path->text());
    if (d->exists()) {
        download->setDownloadDirectory(ui->path->text());
        download->accept();
        return;
    }
    QMessageBox msg;
    msg.information(0, "Bad path", "Path doesn't exist: \n\n" + d->path());
    msg.setFixedSize(700, 200);
}

