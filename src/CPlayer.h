//
// Created by machavi on 6/2/21.
//
#pragma once
#include "CEntity.h"
#include "CGame.h"

class CPlayer : public CEntity {
 public:
  CPlayer();
  ~CPlayer() = default;

 private:
  bool addEntityId(CFileLoaderIt it) override;

 public:
  /**
   * executes one turn
   */
  bool Turn() override;

  /**
   * Facilitates attack action
   * @param toAttack which entity to attack
   * @return true if the attack was successful, false if not (not enough action
   * points, target too far, etc.)
   */
  bool Attack(CEntity& toAttack, const CWeapon& weapon) override;

  /**
   * handles action if the entity is attacked
   * @param attackPower attack damage of the incoming attack
   * @return the damage that has the entity received
   */
  int Attacked(const int attackDamage) override;

  /**
   * facilitates movement
   * @param x
   * @param y
   * @return true if possible else false
   */
  bool Move(const int x, const int y) override;
  static std::shared_ptr<CEntity> Create();
};
