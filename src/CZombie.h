//
// Created by machavi on 5/10/21.
//
#pragma once
#include <memory>

#include "CEntity.h"
#include "CGame.h"
#include "CMovable.h"

class CZombie : public CMovable {
 public:
  CZombie(const string& name, int height, int width, size_t invSize,
           int maxHealth,  int nextLevCoef = 5,
           int defence = 1,  int attack = 2,
           int movement = 3)
      : CMovable(name, height, width, invSize, maxHealth, nextLevCoef, defence,
                 attack, movement) {}

  /**
   * executes one turn
   */
  virtual void Turn(CGame& game);

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
  bool Defense();
  /**
   * handles action if the entity is attacked
   * @param attackPower attack damage of the incoming attack
   * @return the damage that has the entity received
   */
  int Attacked(const int attackDamage);
};
void CZombie::Turn(CGame& game) {
  std::pair<int, int> pos = game.GetPosition(*this);
  std::shared_ptr<CEntity> closest =
      game.GetClosesEntityTo(pos.first, pos.second);
  Attack(closest);
}

bool CZombie::Attack(const CEntity& toAttack) {
  int attPower = GetAttackPower();
  return toAttack.Attacked(attPower);
}

int CZombie::Attacked(const int attackDamage) {
   int health = GetHealth() - attackDamage + GetDefensePower();
  SetHealth(health);
  return health;
}
