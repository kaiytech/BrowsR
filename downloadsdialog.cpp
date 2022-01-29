#include "downloadsdialog.h"
#include "ui_downloadsdialog.h"
#include <QList>
#include <QStandardItem>
#include <QStandardItemModel>

QList<QStandardItem *> prepareRow(const QString &first,
                                              const QString &second,
                                              const QString &third)
{
    return {new QStandardItem(first),
            new QStandardItem(second),
            new QStandardItem(third)};
}

DownloadsDialog::DownloadsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadsDialog)
{
    ui->setupUi(this);

    QList<QStandardItem *> preparedRow = prepareRow("first", "second", "third");
    auto standardModel = new QStandardItemModel(this);
    QStandardItem *item = standardModel->invisibleRootItem();
    // adding a row to the invisible root item produces a root element
    item->appendRow(preparedRow);

    ui->fileList->setModel(standardModel);
    ui->fileList->show();
    ui->fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->fileList->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    ui->fileList->horizontalHeader()->setStretchLastSection(true);
    show();
}


DownloadsDialog::~DownloadsDialog()
{
    delete ui;
}

void DownloadsDialog::on_DownloadsDialog_accepted()
{

}

