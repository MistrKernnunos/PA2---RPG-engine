//
// Created by machavi on 5/9/21.
//
#include "CPlayer.h"

#include "CRoom.h"

bool CPlayer::Attack(const CEntity& toAttack) { return false; }

bool CPlayer::Defense() { return false; }

int CPlayer::Attacked(const int attackDamage) { return 0; }

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
  m_CurrActionPoints = m_ActionPoints;
  m_Controller->Control(*this);
}
std::shared_ptr<CEntity> CPlayer::Create() { return std::make_shared<CPlayer>(); }

bool CPlayer::RecieveMessage(const CMessage& message) { MessageType type = message.GetType(); }
