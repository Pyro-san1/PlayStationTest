#include "FileDownloader.h"

#include "curl/curl.h"

FileDownloader::FileDownloader()
{
}


FileDownloader::~FileDownloader()
{
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void FileDownloader::downloadFile(std::string const & url, std::string const & fileNameFullPath)
{
    CURL *curl;
    FILE *file;
    CURLcode res;
    curl = curl_easy_init();
    if (curl)
    {
        file = fopen(fileNameFullPath.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(file);
    }
}

std::vector<std::string> FileDownloader::downloadFiles(std::vector<std::string> urlList, std::string const & folderPath)
{
    std::vector<std::string> retVal;

    CURL *curl;
    FILE *file;
    CURLcode res;

    for (unsigned int i = 0; i < urlList.size(); ++i)
    {
        std::string fileName;
        size_t sep = urlList[i].find_last_of("\\/");
        if (sep == std::string::npos)
        {
            continue;
        }
        fileName = urlList[i].substr(sep + 1, urlList[i].size() - sep - 1);
        std::string fullPath = folderPath + fileName;
        
        curl = curl_easy_init();
        if (curl)
        {
            file = fopen(fullPath.c_str(), "wb");
            curl_easy_setopt(curl, CURLOPT_URL, urlList[i].c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(file);
            retVal.push_back(fullPath);
        }
    }
    return retVal;
}
