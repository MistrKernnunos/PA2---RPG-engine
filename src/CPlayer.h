//
// Created by machavi on 5/9/21.
//

#include "CMovable.h"

#pragma once

class CPlayer : public CEntity {
 public:
  CPlayer(const string& name, int height, int width, size_t invSize,
          unsigned int maxHealth, unsigned int nextLevCoef = 5,
          unsigned int defence, unsigned int attack)
      : CEntity(name, height, width, invSize, maxHealth, nextLevCoef, defence,
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