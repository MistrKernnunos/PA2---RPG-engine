//
// Created by machavi on 5/10/21.
//
#pragma once
#include <memory>

#include "CEntity.h"

class CZombie : public CEntity {
 public:
 private:
  bool addEntityId(CFileLoaderIt it) override;

 public:
  CZombie();

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
  bool Attack(CEntity& toAttack, const CWeapon& weapon);

  /**
   * entity takes enters defense state until start of next turn
   * @return true if successful, false if not (not enough action points)
   */
  bool Defense();
  /**
   * handles action if the entity is attacked
   * @param attackPower attack damage of the incoming attack
   * @return the damage that has the entity received
   */
  int Attacked(const int attackDamage);

  /**
   *moves entity by x and y
   * @param x
   * @param y
   * @return
   */
  bool Move(const int x, const int y);

  static std::shared_ptr<CEntity> Create();
  bool GetAttacked() const;

 private:
  bool m_Attacked = false;
};
