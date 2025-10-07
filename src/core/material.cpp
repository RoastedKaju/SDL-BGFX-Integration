#include "material.h"

#include <SDL3/SDL.h>

Material::Material(bgfx::ProgramHandle program) : program_(program) {
  // Create a sampler uniform handle for SAMPLER2D(s_texColor, 0)
  sampler_ = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
  diffuse_ = nullptr;
}

Material::~Material() {
  if (bgfx::isValid(sampler_)) {
    bgfx::destroy(sampler_);
  }
}

void Material::SetDiffuse(const Texture& texture) {
  diffuse_ = &texture;
}

void Material::Bind() const {
  if (!diffuse_ || !bgfx::isValid(diffuse_->GetHandle())) {
    SDL_Log("Failed to bind texture with sampler");
    return;
  }

  // Sends the sampler 2D to shader program (GPU)
  bgfx::setTexture(0, sampler_, diffuse_->GetHandle());
}