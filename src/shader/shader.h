#ifndef SHADER_H_
#define SHADER_H_

#include <bgfx/bgfx.h>

class Shader {
 public:
  Shader();
  ~Shader();

  // Load shader from path
  static const bgfx::Memory* Load(const char* path);

  // Create shader program
  void Create(const char* vs_path, const char* fs_path);

  inline bgfx::ProgramHandle GetProgramHandle() const { return program_; }

 private:
  bgfx::ProgramHandle program_;
};

#endif  // !SHADER_H_
