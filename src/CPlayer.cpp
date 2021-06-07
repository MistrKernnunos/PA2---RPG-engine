//
// Created by machavi on 5/9/21.
//
#include "CPlayer.h"

#include "CInterfaceLocator.h"
#include "CMap.h"

bool CPlayer::Attack(CEntity& toAttack, const CWeapon& weapon) {
  if (m_CurrActionPoints >= m_AttackCost) {
    weapon.Attack(toAttack, *this);
    return true;
  }
  return false;
}

int CPlayer::Attacked(const int attackDamage) {
  int damage = attackDamage - (m_DefencePower * m_Level);
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

bool CPlayer::Move(const int x, const int y) {
  CCoordinates end(m_Coordinates.X() + x, m_Coordinates.Y() + y);
  if (m_Room.lock()->Move(m_Coordinates, end, m_Movement) && m_CurrActionPoints >= m_MovementCost) {
    m_Coordinates = end;
    m_Room.lock()->Render();
    m_CurrActionPoints -= m_MovementCost;
    return true;
  }
  return false;
}

bool CPlayer::Turn() {
  if (m_State == ALIVE) {
    m_CurrActionPoints = m_ActionPoints;
    return m_Controller->Control(*this);
  }
  return false;
}
std::shared_ptr<CEntity> CPlayer::Create() { return std::make_shared<CPlayer>(); }
CPlayer::CPlayer() { m_Apperance = "\33[105mP\33[0m"; }
bool CPlayer::addEntityId(CFileLoaderIt it) {
  if (it.GetName() != "entity") {
    return false;
  }
  std::list<std::pair<std::string, std::string>> propList;
  propList.emplace_back("entityID", "player");
  return it.AddProperties(propList);
}
