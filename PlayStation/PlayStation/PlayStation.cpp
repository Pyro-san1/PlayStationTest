// PlayStation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <filesystem>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "FileDownloader.h"
#include "JsonParser.h"

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

    std::vector<std::string> downloadedFiles = downloader.downloadFiles(jsonParser.getPngUrls(), path.string());
    unsigned int currentIndex = 0;

    SDL_Event event;

    SDL_Window* window = NULL;
    SDL_Surface* background_surface = NULL;
    SDL_Texture* background_texture = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "PictureViewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        100,
        100,
        SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    background_surface = IMG_Load(downloadedFiles[currentIndex].c_str());
    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);

    int w;
    int h;

    SDL_QueryTexture(background_texture, NULL, NULL, &w, &h);
    SDL_SetWindowSize(window, w, h);


    while (true)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_RIGHT:
                {
                    if (currentIndex == static_cast<unsigned int>(downloadedFiles.size() - 1))
                    {
                        currentIndex = 0;
                    }
                    else
                    {
                        currentIndex++;
                    }
                    background_surface = IMG_Load(downloadedFiles[currentIndex].c_str());
                    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);
                    break;
                }
                case SDLK_LEFT:
                {
                    if (currentIndex == 0)
                    {
                        currentIndex = static_cast<unsigned int>(downloadedFiles.size() - 1);
                    }
                    else
                    {
                        currentIndex--;
                    }
                    std::cout << "leftPressed" << std::endl;
                    background_surface = IMG_Load(downloadedFiles[currentIndex].c_str());
                    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);
                    break;
                }
            }
            SDL_QueryTexture(background_texture, NULL, NULL, &w, &h);
            SDL_SetWindowSize(window, w, h);
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(background_texture);
    SDL_FreeSurface(background_surface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}