#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <bgfx/bgfx.h>
#include <memory>

#include "material.h"
#include "mesh.h"

class Renderable {
 public:
  Renderable(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

  void Draw(uint8_t viewID) const;

  inline std::shared_ptr<Mesh> GetMesh() const { return mesh_; }
  inline std::shared_ptr<Material> GetMaterial() const { return material_; }

 private:
  std::shared_ptr<Mesh> mesh_;
  std::shared_ptr<Material> material_;
  // Transform
};

#endif  // !RENDERABLE_H_
