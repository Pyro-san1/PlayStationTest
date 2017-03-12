// PlayStation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "SDL.h"
#include "SDL_image.h"

#include "curl/curl.h"

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.dynamsoft.com");
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

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
        320,
        568,
        SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    background_surface = IMG_Load("c:/__cucc/interviews/PlayStation/a.png");
    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);

    int w;
    int h;

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
                    std::cout << "rightPressed" << std::endl;
                    background_surface = IMG_Load("c:/__cucc/interviews/PlayStation/b.png");
                    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);
                    break;
                }
                case SDLK_LEFT:
                {
                    std::cout << "leftPressed" << std::endl;
                    background_surface = IMG_Load("c:/__cucc/interviews/PlayStation/a.png");
                    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);
                    break;
                }
            }
        }

        SDL_QueryTexture(background_texture, NULL, NULL, &w, &h);
        SDL_SetWindowSize(window, w, h);

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

// Get a random number between 0 and 255
int randCol()
{
    return rand() % 255 + 0;
}

/*
int main(int argc, char** argv)
{
    // Initialize the random number generator
    srand(time(NULL));

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Open a 800x600 window and define an accelerated renderer
    SDL_Window* window = SDL_CreateWindow("SDL2 & Code::Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initial renderer color
    SDL_SetRenderDrawColor(renderer, randCol(), randCol(), randCol(), 255);

    bool running = true;
    Uint32 old_time = 0, change_color_time = 1000, new_time;
    SDL_Event event;
    while (running)
    {
        // Check for various events (keyboard, mouse, touch, close)
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                const char* key = SDL_GetKeyName(event.key.keysym.sym);
                if (strcmp(key, "Q") == 0 || strcmp(key, "Escape") == 0)
                {
                    running = false;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Clear buffer
        SDL_RenderClear(renderer);

        // Draw here ...

        // Switch buffers
        SDL_RenderPresent(renderer);

        new_time = SDL_GetTicks();
        if (new_time - old_time > change_color_time)
        {
            SDL_SetRenderDrawColor(renderer, randCol(), randCol(), randCol(), 255);
            old_time = new_time;
        }
    }

    // Release any of the allocated resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/