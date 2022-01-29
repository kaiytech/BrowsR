#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QWebEngineDownloadRequest>


class DownloadManager
{
public:
    DownloadManager();
    void RequestDownload(QWebEngineDownloadRequest *download);
};

DownloadManager *GetDownloadManager();

#endif // DOWNLOADMANAGER_H
