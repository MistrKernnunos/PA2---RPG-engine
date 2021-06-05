//
// Created by machavi on 5/9/21.
//
#include "CPlayer.h"

#include "CInterfaceLocator.h"
#include "CRoom.h"

bool CPlayer::Attack(CEntity& toAttack, const CWeapon& weapon) {
  if (m_CurrActionPoints >= m_AttackCost) {
    weapon.Attack(toAttack, *this);
    return true;
  }
  return false;
}

bool CPlayer::Defense() { return false; }

int CPlayer::Attacked(const int attackDamage) {
  int damage = attackDamage - (m_DefencePower * m_Level);
  damage = damage < 0 ? 0 : damage;
  m_Health -= damage;
  if (m_Health <= 0) {
    m_State = DEAD;
    CInterface interface = CInterfaceLocator::getInerface();
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

void CPlayer::Turn() {
  if (m_State == ALIVE) {
    m_CurrActionPoints = m_ActionPoints;
    m_Controller->Control(*this);
  }
}
std::shared_ptr<CEntity> CPlayer::Create() { return std::make_shared<CPlayer>(); }

