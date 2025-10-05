#include "material.h"

#include <SDL3/SDL.h>

Material::Material(bgfx::ProgramHandle program) : program_(program) {
  // Create a sampler uniform handle for SAMPLER2D(s_texColor, 0)
  sampler_ = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
  texture_ = nullptr;
}

Material::~Material() {
  if (bgfx::isValid(sampler_)) {
    bgfx::destroy(sampler_);
  }
}

void Material::SetTexture(const Texture& texture) {
  texture_ = &texture;
}

void Material::Bind() const {
  if (!texture_ || !bgfx::isValid(texture_->GetHandle())) {
    SDL_Log("Failed to bind texture with sampler");
    return;
  }

  bgfx::setTexture(0, sampler_, texture_->GetHandle());
}