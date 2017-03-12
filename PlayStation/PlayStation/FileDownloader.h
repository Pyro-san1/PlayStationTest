#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <string>
#include <vector>

class FileDownloader
{
public:
    explicit FileDownloader();
    ~FileDownloader();

    void downloadFile(std::string const &url, std::string const &fileNameFullPath);
    std::vector<std::string> downloadFiles(std::vector<std::string> urlList, std::string const &folderPath);
};

#endif //FILEDOWNLOADER_H