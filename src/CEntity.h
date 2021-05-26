//
//
// Created by machavi on 5/7/21.
//
#pragma once
#include <string>
#include <utility>
#include <vector>

#include "CGame.h"
#include "CInventory.h"
#include "CItem.h"
#include "CRoom.h"
class CEntity {
 public:
  /**
   * Constructor
   * @param name name of the entity
   */
  CEntity(const std::string& name, int height, int width, size_t invSize,
          int maxHealth, int nextLevCoef = 0, int defence = 0, int attack = 0)
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
  virtual bool Attack(const CEntity& toAttack) = 0;

  /**
   * entity takes enters defense state until start of next turn
   * @return true if successful, false if not (not enough action points)
   */
virtual  bool Defense() = 0;
  /**
   * handles action if the entity is attacked
   * @param attackPower attack damage of the incoming attack
   * @return the damage that has the entity received
   */
  virtual int Attacked(const int attackDamage) = 0;

  size_t GetHeight() const;

  size_t GetWidth() const;

  int GetMaxHealth() const;

  const std::string& GetName() const;

  int GetHealth() const;

  int GetAttackPower() const;

  int GetDefensePower() const;

  int GetActionPoints() const;

  int GetXP() const;

  int GetLevel() const;

  void SetHealth(int health);

  bool InsertIntoRomm(const CRoom& room);

  const CInventory& GetInventory() const;

  CInventory& GetInventory();

 private:
  // information about the entity
  const std::string m_Name;
  const size_t m_Height;
  const size_t m_Width;
  const int m_MaxHealth;
  const int m_NextLevelCoef = 5;

  // current stats of the entity
  int m_Health;
  int m_DefencePower;
  int m_AttackPower;
  int m_ActionPoints;
  int m_XP = 0;
  int m_Level = 1;
  CRoom m_CurrRoom;
  CInventory m_Inventory;
};
