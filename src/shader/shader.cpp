#include "shader.h"

#include <SDL3/SDL.h>
#include <fstream>

Shader::Shader() {
  program_ = BGFX_INVALID_HANDLE;
}

Shader::~Shader() {
  if (bgfx::isValid(program_)) {
    bgfx::destroy(program_);
  }
}

const bgfx::Memory* Shader::Load(const char* path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    SDL_Log("Failed to load file");
    return nullptr;
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  const bgfx::Memory* mem = bgfx::alloc(uint32_t(size + 1));
  if (!file.read((char*)mem->data, size)) {
    SDL_Log("Failed to read file");
    return nullptr;
  }

  mem->data[size] = '\0';
  return mem;
}

void Shader::Create(const char* vs_path, const char* fs_path) {
  const bgfx::Memory* vs_mem = Shader::Load(vs_path);
  const bgfx::Memory* fs_mem = Shader::Load(fs_path);

  if (!vs_mem || !fs_mem) {
    SDL_Log("Shader memory invalid");
    return;
  }

  bgfx::ShaderHandle vsh = bgfx::createShader(vs_mem);
  bgfx::ShaderHandle fsh = bgfx::createShader(fs_mem);

  if (!bgfx::isValid(vsh)) {
    SDL_Log("Vertex shader is invalid");
  }

  if (!bgfx::isValid(fsh)) {
    SDL_Log("Fragment shader is invalid");
  }

  program_ = bgfx::createProgram(vsh, fsh, true);

  if (!bgfx::isValid(program_)) {
    SDL_Log("Shader program invalid");
  }
}
