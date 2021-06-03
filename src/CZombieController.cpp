//
// Created by machavi on 6/2/21.
//

#include "CZombieController.h"
void CZombieController::Control(CEntity& toControl) {
  // todo jak se ma chovat zombie
}
std::shared_ptr<CControler> CZombieController::Create() { return std::make_shared<CZombieController>(); }
void CZombieController::AttachToEntity(std::weak_ptr<CEntity> entity) {}
