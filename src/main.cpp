#include <iostream>
#include <SDL3/SDL.h>

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) == true)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL video Initialized");
    }

    // Window
    SDL_Window* window = SDL_CreateWindow("My window", 800, 600, SDL_WINDOW_RESIZABLE);
    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_FRect movingRect;
    movingRect.h = 75.0f;
    movingRect.w = 100.0f;
    movingRect.x = 50.0f;
    movingRect.y = 50.0f;

    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                SDL_LogInfo(0, "Quit called");
                SDL_Quit();
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                SDL_LogInfo(0, "Close requested");
                SDL_DestroyWindow(window);
                break;

            case SDL_EVENT_WINDOW_RESIZED:
                SDL_LogInfo(0, "Window resized");
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 150, 150, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &movingRect);

        movingRect.x += 2;

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}