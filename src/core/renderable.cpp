#include "renderable.h"

Renderable::Renderable(std::shared_ptr<Mesh> mesh,
                       std::shared_ptr<Material> material) {
  mesh_ = std::move(mesh);
  material_ = std::move(material);
}

void Renderable::Draw(uint8_t viewID) const {
  if (!mesh_ || !material_) {
    return;
  }
    
  material_->Bind();
  mesh_->Draw(material_->GetProgramHandle(), viewID);
}