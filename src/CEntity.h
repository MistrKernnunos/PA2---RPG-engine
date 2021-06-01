//
//
// Created by machavi on 5/7/21.
//
#pragma once
#include <string>
#include <utility>
#include <vector>

#include "CCoordinates.h"
#include "CGame.h"
#include "CInventory.h"
//#include "CItem.h"
#include "CRoom.h"
class CEntity {
 public:
  /**
   * Constructor
   * @param name name of the entity
   */
  CEntity() = default;
  /**
   * executes one turn
   */
  //    virtual void Turn(CGame& game) = 0;

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
  virtual bool Defense() = 0;
  /**
   * handles action if the entity is attacked
   * @param attackPower attack damage of the incoming attack
   * @return the damage that has the entity received
   */
  virtual int Attacked(const int attackDamage) = 0;

  /**
   * loads stats and inventory from file
   * @param it iterator to entity node
   * @return true if successfully loaded otherwise null
   */
  virtual bool Load(CFileLoaderIt it) = 0;

  const std::string& GetName() const;
  size_t GetHeight() const;
  size_t GetWidth() const;
  int GetMaxHealth() const;
  int GetHealth() const;
  int GetDefencePower() const;
  int GetAttackPower() const;
  int GetActionPoints() const;
  int GetXp() const;
  int GetLevel() const;
  const CCordinates& GetCoordinates() const;

  //  bool InsertIntoRomm(std::shared_ptr<CRoom> room);

  //  CInventory& GetInventory();

  //  const CInventory& GetInventory() const;

 protected:
  // information about the entity
  std::string m_Name;
  size_t m_Height = 1;
  size_t m_Width = 1;
  int m_MaxHealth = 0;
  int m_NextLevelCoef = 5;

  // current stats of the entity
  int m_Health = 0;
  int m_DefencePower = 0;
  int m_AttackPower = 0;
  int m_ActionPoints = 0;
  int m_XP = 0;
  int m_Level = 1;

  CCordinates m_Coordinates;
  //  std::shared_ptr<CRoom> m_CurrRoom;
  CInventory m_Inventory;
};

const std::string& CEntity::GetName() const { return m_Name; }
size_t CEntity::GetHeight() const { return m_Height; }
size_t CEntity::GetWidth() const { return m_Width; }
int CEntity::GetMaxHealth() const { return m_MaxHealth; }
int CEntity::GetHealth() const { return m_Health; }
int CEntity::GetDefencePower() const { return m_DefencePower; }
int CEntity::GetAttackPower() const { return m_AttackPower; }
int CEntity::GetActionPoints() const { return m_ActionPoints; }
int CEntity::GetXp() const { return m_XP; }
int CEntity::GetLevel() const { return m_Level; }
const CCordinates& CEntity::GetCoordinates() const { return m_Coordinates; }
// const CInventory& CEntity::GetInventory() const { return m_Inventory; }
// CInventory& CEntity::GetInventory() { return m_Inventory; }

// bool CEntity::InsertIntoRomm(std::shared_ptr<CRoom> room) { return false; }
