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
  bool move(const int x, const int y);

  static std::shared_ptr<CEntity> Create();

 private:
  bool loadProperties(CFileLoaderIt iterator);
  static std::string loadProperty(CFileLoaderIt& iterator, const std::string& nodeName);
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
  m_Name = loadProperty(iterator, "name");
  iterator.Next();
  iterator.Next();
  m_MaxHealth = std::stoi(loadProperty(iterator, "maxHealth"));
  iterator.Next();
  iterator.Next();
  m_Health = std::stoi(loadProperty(iterator, "health"));
  iterator.Next();
  iterator.Next();
  m_AttackPower = std::stoi(loadProperty(iterator, "attack"));
  iterator.Next();
  iterator.Next();
  m_DefencePower = std::stoi(loadProperty(iterator, "defense"));
  iterator.Next();
  iterator.Next();
  m_ActionPoints = std::stoi(loadProperty(iterator, "actionPoints"));
  iterator.Next();
  iterator.Next();
  m_XP = std::stoi(loadProperty(iterator, "xp"));
  iterator.Next();
  iterator.Next();
  m_Level = std::stoi(loadProperty(iterator, "level"));
  iterator.Next();
  iterator.Next();
  m_Movement = std::stoi(loadProperty(iterator, "movement"));
  iterator.Next();
  iterator.Next();
  m_NextLevelCoef = std::stoi(loadProperty(iterator, "levelCoef"));
  return true;
}
std::string CZombie::loadProperty(CFileLoaderIt& iterator, const std::string& nodeName) {
  std::string res;
  if (iterator.GetName() != nodeName) {
    throw std::invalid_argument("wrong property name name");
    return res;
  }
  res = iterator.GetContent();
  return res;
}
