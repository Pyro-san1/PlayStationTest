// PlayStation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <filesystem>

#include "FileDownloader.h"
#include "JsonParser.h"
#include "PicViewer.h"

std::string Usage()
{
    std::string CRLF = "\r\n";
    std::string usage;
    usage += "---------------------------------------------------------";
    usage += CRLF;
    usage += "See proper parameterlist and order below:";
    usage += CRLF;
    usage += "  PlayStation.exe pngFilesInThisJson.json";
    usage += CRLF;
    usage += CRLF;
    usage += "pngFilesInThisJson.json must contain at least one link or full path to a png file!:";
    usage += CRLF;
    usage += "---------------------------------------------------------";
    usage += CRLF;

    return usage;
}

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        std::cout << "Error: Not enough parameters." << std::endl;
        std::cout << Usage() << std::endl;
        return -1;
    }

    std::experimental::filesystem::path path = std::experimental::filesystem::current_path();
    path += "\\";
    path += "Download\\";
    std::experimental::filesystem::create_directory(path);

    std::string const jsonFileName = path.string() + "pngList.json";

    FileDownloader downloader;
    downloader.downloadFile(argv[1], jsonFileName);

    JsonParser jsonParser;
    jsonParser.parseJson(jsonFileName);

    PicViewer picViewer(downloader.downloadFiles(jsonParser.getPngUrls(), path.string()));
    picViewer.run();

    return 0;
}