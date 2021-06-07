//
// Created by machavi on 5/10/21.
//
#include "CZombie.h"

#include "CInterfaceLocator.h"
#include "CMap.h"
std::shared_ptr<CEntity> CZombie::Create() { return std::make_shared<CZombie>(); }

CZombie::CZombie() { m_Apperance = "\33[105mZ\33[0m"; }

bool CZombie::Attack(CEntity& toAttack, const CWeapon& weapon) {
  if (m_CurrActionPoints >= m_AttackCost) {
    weapon.Attack(toAttack, *this);
    return true;
  }
  return false;
}

int CZombie::Attacked(const int attackDamage) {
  m_Attacked = true;
  int damage = attackDamage - m_DefencePower;
  damage = damage < 0 ? 0 : damage;
  m_Health -= damage;
  if (m_Health <= 0) {
    m_State = DEAD;
    m_Lootable = true;
    CInterface interface = CInterfaceLocator::getInterface();
    std::string message = GetName();
    message += " died.";
    interface.Message(message);
  }
  return damage;
}
bool CZombie::Turn() {
  if (m_State == ALIVE) {
    m_CurrActionPoints = m_ActionPoints;
    m_Controller->Control(*this);
    m_Attacked = false;
  }
  return true;
}

bool CZombie::Move(const int x, const int y) {
  CCoordinates end(m_Coordinates.X() + x, m_Coordinates.Y() + y);
  if (m_Room.lock()->Move(m_Coordinates, end, m_Movement) && m_CurrActionPoints >= m_MovementCost) {
    m_Coordinates = end;
//    m_Room.lock()->Render();
    m_CurrActionPoints -= m_MovementCost;
    return true;
  }
  return false;
}
bool CZombie::GetAttacked() const { return m_Attacked; }
bool CZombie::addEntityId(CFileLoaderIt it) {
  if (it.GetName() != "entity") {
    return false;
  }
  std::list<std::pair<std::string, std::string>> propList;
  propList.emplace_back("entityID", "zombie");
  return it.AddProperties(propList);
}
