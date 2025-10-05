#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <bgfx/bgfx.h>
#include "texture.h"

class Material {
 public:
  Material(bgfx::ProgramHandle program);
  ~Material();

  void SetTexture(const Texture& texture);

  void Bind() const;

  inline bgfx::ProgramHandle GetProgramHandle() const { return program_; }

 private:
  bgfx::ProgramHandle program_;
  bgfx::UniformHandle sampler_;

  const Texture* texture_;
};

#endif  // !MATERIAL_H_
