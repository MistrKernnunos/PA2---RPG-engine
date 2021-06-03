//
// Created by machavi on 5/10/21.
//
#pragma once
#include "CEntity.h"

class CChest : public CEntity {
  CChest(const string& name = "chest", int height = 2, int width = 2,
         size_t invSize = 100,  int maxHealth = 100,
          int nextLevCoef = 5,  int defence = 1000,
          int attack = 0)
      : CEntity(name, height, width, invSize, maxHealth, nextLevCoef, def,
                attack) {}
  /**
   * executes one turn
   */
  virtual void Turn();

  /**
   * Facilitates attack action
   * @param toAttack which entity to attack
   * @return true if the attack was successful, false if not (not enough action
   * points, target too far, etc.)
   */
  bool Attack(const CEntity& toAttack);

  /**
   * entity takes enters defense state until start of next turn
   * @return true if successful, false if not (not enough action points)
   */
  bool Defense() = 0;
  /**
   * handles action if the entity is attacked
   * @param attackPower attack damage of the incoming attack
   * @return the damage that has the entity received
   */
  int Attacked(const int attackDamage);
};

void CChest::Turn() {
  // chest does nothing in her turn
}

bool CChest::Attack(const CEntity& toAttack) {
  // chest does not attack
}
int CChest::Attacked(const int attackDamage) {
  return -1  // chest cant be attacked
}

bool CChest::Defense() {
  return false  // chest cant enter defense state
}