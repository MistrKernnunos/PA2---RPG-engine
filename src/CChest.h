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
  bool addEntityId(CFileLoaderIt it) override;

 public:
  ;

  /**
   * executes one turn
   */
  virtual bool Turn();

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

  /*
   * returns blank Chest as shared pointer
   */
  static std::shared_ptr<CEntity> Create();

  bool Move(const int x, const int y) override;
};
