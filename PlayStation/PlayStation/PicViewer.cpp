#include "PicViewer.h"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

PicViewer::PicViewer(std::vector<std::string> const &downloadedFiles):
    mDownloadedFiles(downloadedFiles)
{
}

PicViewer::~PicViewer()
{
}

void PicViewer::run()
{
    if (0 == mDownloadedFiles.size())
    {
        std::cout << "No files downloaded. No images to show." << std::endl;
        return;
    }

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
    background_surface = IMG_Load(mDownloadedFiles[mCurrentIndex].c_str());
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
                    background_surface = IMG_Load(mDownloadedFiles[nextIndex()].c_str());
                    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);
                    break;
                }
                case SDLK_LEFT:
                {
                    background_surface = IMG_Load(mDownloadedFiles[previousIndex()].c_str());
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
}

unsigned int PicViewer::nextIndex()
{
    if (mCurrentIndex == static_cast<unsigned int>(mDownloadedFiles.size() - 1))
    {
        mCurrentIndex = 0;
        return mCurrentIndex;
    }

    return ++mCurrentIndex;
}

unsigned int PicViewer::previousIndex()
{
    if (mCurrentIndex == 0)
    {
        mCurrentIndex = static_cast<unsigned int>(mDownloadedFiles.size() - 1);
        return mCurrentIndex;
    }

    return --mCurrentIndex;
}
