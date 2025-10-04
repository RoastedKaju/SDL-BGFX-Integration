#include "texture.h"

#include <SDL3/SDL.h>
#include <bimg/decode.h>
#include <bx/allocator.h>
#include <fstream>
#include <vector>

Texture::Texture() {
  // Defaults
  texture_handle_ = BGFX_INVALID_HANDLE;
  width_ = 0;
  height_ = 0;
}

Texture::~Texture() {
  if (bgfx::isValid(texture_handle_)) {
    bgfx::destroy(texture_handle_);
  }
}

void Texture::Load(const char* path) {
  // Open and read the texture file
  std::ifstream file(path, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    SDL_Log("Failed to open texture file.");
    return;
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(size);
  if (!file.read((char*)buffer.data(), size)) {
    SDL_Log("Failed to read texture file");
    return;
  }

  // Decode the image file
  static bx::DefaultAllocator allocator;
  bimg::ImageContainer* image =
      bimg::imageParse(&allocator, buffer.data(), (uint32_t)size);

  if (!image) {
    SDL_Log("Failed to decode image");
    return;
  }

  width_ = (uint16_t)image->m_width;
  height_ = (uint16_t)image->m_height;

  // Create texture handle
  texture_handle_ = bgfx::createTexture2D(
      width_, height_, image->m_numMips > 1, image->m_numLayers,
      (bgfx::TextureFormat::Enum)image->m_format, 0,
      bgfx::copy(image->m_data, image->m_size));

  bimg::imageFree(image);

  if (!bgfx::isValid(texture_handle_)) {
    SDL_Log("Failed to create texture handle");
    return;
  }
}