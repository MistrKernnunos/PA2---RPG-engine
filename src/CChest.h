//
// Created by machavi on 5/10/21.
//
#pragma once
#include "CEntity.h"

class CChest : public CEntity {
 public:
  CChest() {
    m_Lootable = true;
    m_Apperance = "\33[105mT\33[0m";
  }

 private:
  /**
   * save utility function. Adds entityID to entity node
   * @param it iterator to entity node
   * @return true if successful
   */
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
  bool Attack(CEntity& toAttack, const CWeapon& weapon);

  /**
   * handles action if the entity is attacked
   * @param attackPower attack damage of the incoming attack
   * @return the damage that has the entity received
   */
  int Attacked(const int attackDamage) override;

  /*
   * returns blank Chest as shared pointer
   */
  static std::shared_ptr<CEntity> Create();

  /**
   * does nothing it is stationary chest
   * @param x
   * @param y
   * @return false all the time
   */
  bool Move(const int x, const int y) override;
};
