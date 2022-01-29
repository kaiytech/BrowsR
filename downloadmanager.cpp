#include "downloadmanager.h"
#include "downloadprompt.h"

DownloadManager* __downloadManager;

DownloadManager *GetDownloadManager() {
    if (__downloadManager == nullptr)
        __downloadManager = new DownloadManager();

    return __downloadManager;
}

DownloadManager::DownloadManager()
{

}

void DownloadManager::RequestDownload(QWebEngineDownloadRequest *download)
{
    downloadprompt dp;
    dp.populate(download);
    dp.exec();
}
