#include <SDL3/SDL.h>
#define NOMINMAX
#include <Windows.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <iostream>
#include <string>

#include "core/mesh.h"
#include "shader/shader.h"
#include "utils/vertex_types.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void ResetBgfxView(const SDL_WindowEvent& windowEvent);

int main() {
  bool is_running = true;

  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Failed to Initialize SDL");
    return 1;
  }

  // SDL window
  SDL_Window* main_window = SDL_CreateWindow(
      "sdl-bgfx window", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

  if (!main_window) {
    SDL_Log("Main window is null");
    SDL_Quit();
    return 1;
  }

  // Backend system window
  HWND hwnd =
      (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(main_window),
                                   SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);

  if (!hwnd) {
    SDL_Log("Failed to get HWND");
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 1;
  }

  // BGFX initialize
  bgfx::PlatformData platform_data{};
  platform_data.nwh = hwnd;

  bgfx::setPlatformData(platform_data);

  bgfx::Init init;
  init.type = bgfx::RendererType::OpenGL;
  init.resolution.width = SCREEN_WIDTH;
  init.resolution.height = SCREEN_HEIGHT;
  init.resolution.reset = BGFX_RESET_VSYNC;
  init.platformData = platform_data;

  if (!bgfx::init(init)) {
    SDL_Log("BGFX failed to initialize");
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 1;
  }

  // Enable BGFX debug text
  bgfx::setDebug(BGFX_DEBUG_TEXT);

  // Set BGFX view
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f,
                     0);
  bgfx::setViewRect(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  // Shader
  Shader shader;
  shader.Create("shaders/vs_basic.bin", "shaders/fs_basic.bin");

  // Buffer layout
  PosColorVertex::init();

  // Example triangle
  PosColorVertex verts[] = {
      {0.0f, 0.5f, 0.0f},
      {-0.5f, -0.5f, 0.0f},
      {0.5f, -0.5f, 0.0f},
  };

  uint16_t indices[] = {0, 1, 2};

  Mesh triangle(verts, 3, indices, 3);

  // Main loop
  while (is_running) {
    SDL_Event event;
    // Event loop
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
          is_running = false;
          break;

        case SDL_EVENT_QUIT:
          is_running = false;
          break;

        case SDL_EVENT_WINDOW_RESIZED:
          ResetBgfxView(event.window);
          break;

        default:
          break;
      }
    }

    // BGFX render call
    bgfx::touch(0);

    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 1, 0x4f, "Hello from BGFX!");

    triangle.Draw(shader.GetProgramHandle());

    bgfx::frame();
  }

  bgfx::shutdown();
  SDL_DestroyWindow(main_window);
  SDL_Quit();

  return 0;
}

void ResetBgfxView(const SDL_WindowEvent& windowEvent) {
  const int new_width = windowEvent.data1;
  const int new_height = windowEvent.data2;
  bgfx::reset(new_width, new_height, BGFX_RESET_VSYNC);
  bgfx::setViewRect(0, 0, 0, new_width, new_height);
}