//
// Created by machavi on 6/4/21.
//

#pragma once
#include "CEntity.h"
#include "CWeapon.h"

class CSword : public CWeapon {
 public:
  CSword() = default;
  bool Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) override;
  /**
   * function to attack entity
   * @param toAttack entity to attack
   * @param user entity that is using the weapon
   */
  void Attack(CEntity &toAttack, CEntity &user) const override;
  /*
   * creates empty sword
   */
  static std::unique_ptr<CWeapon> Create();

 private:
  /**
   * utility function for saving weaponID as node property
   * @param it iterator to node
   * @return true if successfully
   */
  bool addEntityID(CFileLoaderIt it) const override;

 public:
  std::string PrintToString() override;
};
