#ifndef PICVIEWER_H
#define PICVIEWER_H

#include <vector>

class PicViewer
{
public:
    explicit PicViewer(std::vector<std::string> const &downloadedFiles);
    ~PicViewer();

    void run();

private:
    unsigned int nextIndex();
    unsigned int previousIndex();

    unsigned int mCurrentIndex = 0;
    std::vector<std::string> mDownloadedFiles;
};

#endif //PICVIEWER_H