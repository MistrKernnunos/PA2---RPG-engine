//
// Created by machavi on 6/2/21.
//

#include "CZombieController.h"

#include <random>

#include "CEntity.h"
enum DIRECTION { HORIZONTAL, VERTICAL };

void CZombieController::Control(CEntity& toControl) {
  idleMove(toControl);
  // todo jak se ma chovat zombie
}
// specify length of first tried step
int CZombieController::m_FirstStep = 3;

std::shared_ptr<CControler> CZombieController::Create() { return std::make_shared<CZombieController>(); }
void CZombieController::idleMove(CEntity& toControl) {
  // random number generation init
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, 1);
  // move vertically or horizontally
  int x = 0;
  int y = 0;
  DIRECTION direction = HORIZONTAL;
  if (distribution(gen)) {
    x = m_FirstStep;
  } else {
    y = m_FirstStep;
    direction = VERTICAL;
  }
  while (!toControl.Move(x, y)) {
    if (1 != std::abs(x)) {
      x += x > 0 ? -1 : 1;
    } else if (x == 1 and direction == HORIZONTAL) {
      x = -m_FirstStep;
    } else if (x == -1) {
      break;
    }
  }
}
void CZombieController::underAttack(CEntity& toControl) {}
