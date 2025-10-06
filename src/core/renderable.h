#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <memory>

#include "material.h"
#include "mesh.h"

class Renderable {
 public:
  Renderable(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

  void Draw(uint8_t viewID) const;

  inline std::shared_ptr<Mesh> GetMesh() const { return mesh_; }
  inline std::shared_ptr<Material> GetMaterial() const { return material_; }

  void SetPosition(const bx::Vec3& pos);
  void SetRotation(const bx::Vec3& rot);

 private:
  void UpdateTransform();

  std::shared_ptr<Mesh> mesh_;
  std::shared_ptr<Material> material_;

  bx::Vec3 position_;
  bx::Vec3 rotation_;

  float transform_[16];
};

#endif  // !RENDERABLE_H_
