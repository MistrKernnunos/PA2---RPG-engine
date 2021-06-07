//
// Created by machavi on 6/2/21.
//

#include "CZombieController.h"

#include <random>

#include "CEntity.h"
#include "CZombie.h"

bool CZombieController::Control(CEntity& toControl) {
  auto & entity = dynamic_cast<CZombie&>(toControl);
  if (entity.GetAttacked()) {
    underAttack(toControl);
  } else {
    idleMove(toControl);
  }

  return true;
}
// specify length of first tried step
int CZombieController::m_FirstStep = 3;

std::shared_ptr<CControler> CZombieController::Create() { return std::make_shared<CZombieController>(); }
void CZombieController::idleMove(CEntity& toControl) {
  // random number generation init
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(-1, 1);
  // move vertically or horizontally
  int x = distribution(gen) * m_FirstStep;
  int y = distribution(gen) * m_FirstStep;
  while (!toControl.Move(x, y) && toControl.GetCurrActionPoints() > toControl.GetMovementCost()) {
    if (1 != std::abs(x)) {
      x += x > 0 ? -1 : 1;
      y += y > 0 ? -1 : 1;
    } else {
      x = distribution(gen) * m_FirstStep;
      y = distribution(gen) * m_FirstStep;
    }
  }
}
void CZombieController::underAttack(CEntity& toControl) {
  auto entities = toControl.GetEntitiesInRange(toControl.GetMovement() * 1.5);
  if (entities.empty()) {
    return;
  }
  CCoordinates curr = toControl.GetCoordinates();
  CCoordinates pos = entities.front()->GetCoordinates();
  int x = pos.X() - curr.X();
  int y = pos.Y() - curr.Y();
  x += x > 0 ? -1 : 1;
  y += y > 0 ? -1 : 1;
  while (!toControl.Move(x, y) && toControl.GetCurrActionPoints() > toControl.GetMovementCost()) {
    x += x > 0 ? -1 : 1;
    y += y > 0 ? -1 : 1;
  }
  const CInventory& inv(toControl.GetInventory());
  auto& weapon = inv.GetWeaponInventory().front();
  if (weapon) {
  }
  toControl.Attack(*entities.front(), *weapon);
}
