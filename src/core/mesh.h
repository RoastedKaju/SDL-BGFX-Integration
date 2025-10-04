#ifndef _MESH_H_
#define _MESH_H_

#include <bgfx/bgfx.h>
#include "utils/vertex_types.h"

class Mesh {
 public:
  Mesh(const PosColorTexVertex* vertices, uint32_t num_vertices,
       const uint16_t* indices, uint32_t num_indices);
  ~Mesh();

  void Draw(bgfx::ProgramHandle handle, uint8_t view_id = 0) const;

 private:
  bgfx::VertexBufferHandle vbh_;
  bgfx::IndexBufferHandle ibh_;
};

#endif  // !_MESH_H_
