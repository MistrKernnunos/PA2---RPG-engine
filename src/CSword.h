//
// Created by machavi on 6/4/21.
//

#pragma once
#include "CEntity.h"
#include "CWeapon.h"

class CSword : public CWeapon {
 public:
  CSword() = default;
  bool Defense(std::shared_ptr<CEntity> user) override;
  bool Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) override;
  bool Attack(CEntity &toAttack, CEntity &user) const override;
  static std::unique_ptr<CWeapon> Create();

 private:
  bool addEntityID(CFileLoaderIt it) const override;

 public:
  std::string PrintToString() override;
};
