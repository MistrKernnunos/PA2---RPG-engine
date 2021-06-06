//
// Created by machavi on 5/10/21.
//
#include "CZombie.h"

#include "CRoom.h"
std::shared_ptr<CEntity> CZombie::Create() { return std::make_shared<CZombie>(); }

// void CZombie::Turn(CGame& game) {}

bool CZombie::Attack(CEntity& toAttack, const CWeapon& weapon) {
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
void CZombie::Turn() {
  // todo
}

bool CZombie::Move(const int x, const int y) {
  return false;
  // todo
}
