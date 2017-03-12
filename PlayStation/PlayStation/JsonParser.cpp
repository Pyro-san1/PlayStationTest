#include "JsonParser.h"

#include <iostream>
#include <fstream>

#include "json\json.h"

JsonParser::JsonParser()
{
}


JsonParser::~JsonParser()
{
}

void JsonParser::parseJson(std::string const & fileFullPath)
{
    Json::Value root;
    Json::Reader reader;

    std::ifstream file(fileFullPath);
    std::string line;
    std::string jsonFile;
    while (std::getline(file, line))
    {
        jsonFile += line;
    }

    bool parsingSuccessful = reader.parse(jsonFile, root, false);

    if (!parsingSuccessful)
    {
        // report to the user the failure and their locations in the document.
        std::cout << "Failed to parse configuration" << std::endl << reader.getFormattedErrorMessages() << std::endl;
        return;
    }

    mTitle = root.get("title", "Images").asString();

    const Json::Value images = root["images"];
    for (unsigned int index = 0; index < images.size(); ++index)  // Iterates over the sequence elements.
    {
        mPngUrls.push_back(images[index].asString());
    }
}
