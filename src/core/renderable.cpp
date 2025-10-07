#include "renderable.h"

Renderable::Renderable(const std::shared_ptr<Mesh>& mesh,
                       const std::shared_ptr<Material>& material)
    : position_(bx::Vec3(0.0f)), rotation_(bx::Vec3(0.0f)) {
  mesh_ = mesh;
  material_ = material;
  bx::mtxIdentity(transform_);
}

void Renderable::Draw(uint8_t viewID) const {
  if (!mesh_ || !material_) {
    return;
  }
  // Send model matrix to shader
  bgfx::setTransform(transform_);

  // Bind the material
  material_->Bind();
  // Draw mesh by submitting the VBH and IBH
  mesh_->Draw(material_->GetProgramHandle(), viewID);
}

void Renderable::SetPosition(const bx::Vec3& pos) {
  position_ = pos;
  UpdateTransform();
}

void Renderable::SetRotation(const bx::Vec3& rot) {
  rotation_ = rot;
  UpdateTransform();
}

void Renderable::UpdateTransform() {
  // Reset the model matrix
  bx::mtxIdentity(transform_);

  // Apply rotation
  float rot_matrix[16];
  bx::mtxRotateXYZ(rot_matrix, rotation_.x, rotation_.y, rotation_.z);
  bx::mtxMul(transform_, rot_matrix, transform_);

  // Apply position
  float pos_matrix[16];
  bx::mtxTranslate(pos_matrix, position_.x, position_.y, position_.z);
  bx::mtxMul(transform_, pos_matrix, transform_);
}