#include "mesh.h"

Mesh::Mesh(const PosColorVertex* vertices, uint32_t num_vertices,
           const uint16_t* indices, uint32_t num_indices) {
  const bgfx::Memory* vb_mem =
      bgfx::copy(vertices, num_vertices * sizeof(PosColorVertex));

  const bgfx::Memory* ib_mem =
      bgfx::copy(indices, num_indices * sizeof(uint16_t));

  // Create buffers
  vbh_ = bgfx::createVertexBuffer(vb_mem, PosColorVertex::layout);
  ibh_ = bgfx::createIndexBuffer(ib_mem);
}

Mesh::~Mesh() {
  if (bgfx::isValid(vbh_))
    bgfx::destroy(vbh_);

  if (bgfx::isValid(ibh_))
    bgfx::destroy(ibh_);
}

void Mesh::Draw(bgfx::ProgramHandle handle, uint8_t view_id) const {
  bgfx::setVertexBuffer(0, vbh_);
  bgfx::setIndexBuffer(ibh_);
  bgfx::submit(view_id, handle);
}
