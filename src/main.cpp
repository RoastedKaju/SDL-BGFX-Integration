#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <bx/platform.h>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) == true) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL video Initialized");
  }

  // Window
  SDL_Window* window = SDL_CreateWindow("My window", SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
  // Renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

  SDL_FRect movingRect;
  movingRect.h = 75.0f;
  movingRect.w = 100.0f;
  movingRect.x = 50.0f;
  movingRect.y = 50.0f;

  // Input direction
  std::pair<float, float> inputDirection{0.0f, 0.0f};

  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
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

          // Key down
        case SDL_EVENT_KEY_DOWN:
          if (event.key.scancode == SDL_SCANCODE_UP) {
            inputDirection.first = -1.0f;
          }
          if (event.key.scancode == SDL_SCANCODE_DOWN) {
            inputDirection.first = 1.0f;
          }
          if (event.key.scancode == SDL_SCANCODE_LEFT) {
            inputDirection.second = -1.0f;
          }
          if (event.key.scancode == SDL_SCANCODE_RIGHT) {
            inputDirection.second = 1.0f;
          }
          break;

          // Key up
        case SDL_EVENT_KEY_UP:
          if (event.key.scancode == SDL_SCANCODE_UP) {
            inputDirection.first = 0.0f;
          }
          if (event.key.scancode == SDL_SCANCODE_DOWN) {
            inputDirection.first = 0.0f;
          }
          if (event.key.scancode == SDL_SCANCODE_LEFT) {
            inputDirection.second = 0.0f;
          }
          if (event.key.scancode == SDL_SCANCODE_RIGHT) {
            inputDirection.second = 0.0f;
          }
          break;

        default:
          break;
      }
    }

    // Clear and set background color
    SDL_SetRenderDrawColor(renderer, 0, 150, 150, 255);
    SDL_RenderClear(renderer);

    // Render a rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &movingRect);

    // Rectangle movement logic
    float proposedY = movingRect.y + 2 * inputDirection.first;
    float proposedX = movingRect.x + 2 * inputDirection.second;

    if (proposedY < 0) {
      proposedY = 0;
    } else if (proposedY + movingRect.h > SCREEN_HEIGHT) {
      proposedY = SCREEN_HEIGHT - movingRect.h;
    }

    movingRect.y = proposedY;

    if (proposedX < 0) {
      proposedX = 0;
    } else if (proposedX + movingRect.w > SCREEN_WIDTH) {
      proposedX = SCREEN_WIDTH - movingRect.w;
    }

    movingRect.x = proposedX;

    // Submit frame
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  SDL_Quit();
  return 0;
}