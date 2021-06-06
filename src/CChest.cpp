//
// Created by machavi on 6/6/21.
//
#include "CChest.h"

void CChest::Turn() {
  // chest does nothing in her turn
}

bool CChest::Attack(CEntity& toAttack, const CWeapon& weapon) {
  // chest does not attack
  return false;
}
int CChest::Attacked(const int attackDamage) {
  return -1;  // chest cant be attacked
}

bool CChest::Defense() {
  return false;  // chest cant enter defense state
}
std::shared_ptr<CEntity> CChest::Create() { return std::make_shared<CChest>(); }

bool CChest::Move(const int x, const int y) { return false; }
