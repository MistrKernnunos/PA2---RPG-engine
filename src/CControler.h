//
// Created by machavi on 6/2/21.
//
#pragma once
class CEntity;
#include <memory>

class CControler {
 public:
  CControler() = default;
  virtual ~CControler() = default;
  virtual void AttachToEntity(std::weak_ptr<CEntity> entity) = 0;
  virtual void Control(CEntity& toControl) = 0;


 protected:
  std::weak_ptr<CEntity> m_Entity;
};
