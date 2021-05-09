//
//
// Created by machavi on 5/7/21.
//
#include <string>
#include <utility>
#include <vector>

#include "CGame.h"
#include "CInventory.h"
#include "CItem.h"
#pragma once

class CEntity {
 public:
  /**
   * Constructor
   * @param name name of the entity
   */
  CEntity(const std::string& name, int height, int width, size_t invSize,
          unsigned int maxHealth, unsigned int nextLevCoef = 5,
          unsigned int defence = 0, unsigned int attack = 0)
      : m_Name(name),
        m_Height(height),
        m_Width(width),
        m_Inventory(invSize),
        m_MaxHealth(maxHealth),
        m_NextLevelCoef(nextLevCoef),
        m_Health(maxHealth),
        m_DefencePower(defence),
        m_AttackPower(attack) {}
  /**
   * executes one turn
   */
  virtual void Turn(CGame& game) = 0;

  /**
   * Facilitates attack action
   * @param toAttack which entity to attack
   * @return true if the attack was successful, false if not (not enough action
   * points, target too far, etc.)
   */
  bool Attack(const CEntity& toAttack) = 0;

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
  int Attacked(const int attackDamage) = 0;

  size_t GetHeight() const;

  size_t GetWidth() const;

  unsigned int GetMaxHealth() const;

  const string& GetName() const;

  unsigned int GetHealth() const;

  unsigned int GetAttackPower() const;

  unsigned int GetDefensePower() const;

  unsigned int GetActionPoints() const;

  unsigned int GetXP() const;

  unsigned int GetLevel() const;

  void SetHealth(unsigned int health);

  const CInventory& GetInventory() const;

  CInventory& GetInventory();

 private:
  // information about the entity
  const string m_Name;
  const size_t m_Height;
  const size_t m_Width;
  const unsigned int m_MaxHealth;
  const unsigned int m_NextLevelCoef;

  // current stats of the entityA
  unsigned int m_Health;
  unsigned int m_DefencePower;
  unsigned int m_AttackPower;
  unsigned int m_ActionPoints;
  unsigned int m_XP = 0;
  unsigned int m_Level = 1;
  CInventory m_Inventory
};
