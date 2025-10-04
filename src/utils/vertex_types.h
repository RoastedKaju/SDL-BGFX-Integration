#ifndef _VERTEX_TYPES_H_
#define _VERTEX_TYPES_H_

#include <bgfx/bgfx.h>

struct PosColorTexVertex {
  float x;
  float y;
  float z;
  uint32_t abgr;
  float u;
  float v;

  static bgfx::VertexLayout layout;

  static void init() {
    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
  }
};

inline bgfx::VertexLayout PosColorTexVertex::layout;

#endif  // !_VERTEX_TYPES_H_
