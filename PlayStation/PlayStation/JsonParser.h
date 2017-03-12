#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <vector>

class JsonParser
{
public:
    explicit JsonParser();
    ~JsonParser();

    void parseJson(std::string const &fileFullPath);
    inline std::vector<std::string> &getPngUrls() { return mPngUrls; }

private:
    std::string mTitle;
    std::vector<std::string> mPngUrls;
};

#endif //JSONPARSER_H