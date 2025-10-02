#ifndef _VERTEX_TYPES_H_
#define _VERTEX_TYPES_H_

#include <bgfx/bgfx.h>

struct PosColorVertex {
  float x;
  float y;
  float z;

  static bgfx::VertexLayout layout;

  static void init() {
    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .end();
  }
};

inline bgfx::VertexLayout PosColorVertex::layout;

#endif  // !_VERTEX_TYPES_H_
