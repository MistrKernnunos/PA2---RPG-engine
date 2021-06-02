//
// Created by machavi on 5/10/21.
//
#pragma once
#include <memory>

#include "CEntity.h"
//#include "CGame.h"

class CZombie : public CEntity {
 public:
  CZombie() = default;

  /**
   * executes one turn
   */
  //  virtual void Turn(CGame& game);

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
  /**
   * loads stats and inventory from file
   * @param it iterator to entity node
   * @return true if successfully loaded otherwise null
   */
  bool Load(CFileLoaderIt it);

  /**
   *moves entity by x and y
   * @param x
   * @param y
   * @return
   */
  //  bool Move(const int x, const int y, CGame& game);

  static std::shared_ptr<CEntity> Create();

 private:
  bool loadProperties(CFileLoaderIt iterator);
};
std::shared_ptr<CEntity> CZombie::Create() { return std::make_shared<CZombie>(); }

// void CZombie::Turn(CGame& game) {}

bool CZombie::Attack(const CEntity& toAttack) {
  return true;
  // todo
}

int CZombie::Attacked(const int attackDamage) {
  return m_Health;
  // todo
}
bool CZombie::Defense() {
  return false;
  // todo
}
bool CZombie::move(const int x, const int y) {
  return false;
  // todo
}

bool CZombie::Load(CFileLoaderIt iterator) {
  if (iterator.GetName() != "entity") {
    throw std::invalid_argument("wrong entity node");
    return false;
  }
  iterator.Child();
  iterator.Next();
  if (!loadProperties(iterator)) return false;
  iterator.Next();
  iterator.Next();
  if (!(m_Coordinates.Load(iterator))) return false;
  iterator.Next();
  iterator.Next();
  if (!(m_Inventory.Load(iterator))) return false;
  return true;
}

bool CZombie::loadProperties(CFileLoaderIt iterator) {
  if (iterator.GetName() != "properties") {
    throw std::invalid_argument("wrong property node");
    return false;
  }
  // todo misto loadProperty pouzit it.getContent(nodename)
  iterator.Child();
  iterator.Next();
  m_Name = iterator.GetContent("name");
  iterator.Next(2);
  m_MaxHealth = std::stoi(iterator.GetContent("maxHealth"));
  iterator.Next(2);
  m_Health = std::stoi(iterator.GetContent("health"));
  iterator.Next(2);
  m_AttackPower = std::stoi(iterator.GetContent("attack"));
  iterator.Next(2);
  m_DefencePower = std::stoi(iterator.GetContent("defense"));
  iterator.Next(2);
  m_ActionPoints = std::stoi(iterator.GetContent("actionPoints"));
  iterator.Next(2);
  m_XP = std::stoi(iterator.GetContent("xp"));
  iterator.Next(2);
  m_Level = std::stoi(iterator.GetContent("level"));
  iterator.Next(2);
  m_Movement = std::stoi(iterator.GetContent("movement"));
  iterator.Next(2);
  m_NextLevelCoef = std::stoi(iterator.GetContent("levelCoef"));
  return true;
}
