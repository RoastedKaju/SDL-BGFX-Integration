#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <memory>

#include "material.h"
#include "mesh.h"

// Renderable references the meshes loaded into memory and creates instances
class Renderable {
 public:
  Renderable(const std::shared_ptr<Mesh>& mesh,
             const std::shared_ptr<Material>& material);

  void Draw(uint8_t viewID) const;

  inline std::shared_ptr<Mesh> GetMesh() const { return mesh_; }
  inline std::shared_ptr<Material> GetMaterial() const { return material_; }

  void SetPosition(const bx::Vec3& pos);
  void SetRotation(const bx::Vec3& rot);

 private:
  // Recreates the model matrix after you have changed position, rotation or scale
  void UpdateTransform();

  std::shared_ptr<Mesh> mesh_;          // Pointer to mesh in memory
  std::shared_ptr<Material> material_;  // Pointer to material in memory

  bx::Vec3 position_;
  bx::Vec3 rotation_;

  float transform_[16];
};

#endif  // !RENDERABLE_H_
