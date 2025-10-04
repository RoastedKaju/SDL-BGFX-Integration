#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <bgfx/bgfx.h>

class Texture {
 public:
  Texture();
  ~Texture();

  void Load(const char* path);

  inline const bgfx::TextureHandle& GetHandle() const {
    return texture_handle_;
  }

 private:
  bgfx::TextureHandle texture_handle_;

  uint16_t width_;
  uint16_t height_;
};

#endif  // !TEXTURE_H_
