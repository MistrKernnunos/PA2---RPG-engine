//
// Created by machavi on 6/2/21.
//

#include "CPlayerController.h"

#include "CEntity.h"
#include "CInterfaceLocator.h"
#include "CPlayer.h"
void CPlayerController::Control(CEntity& toControl) {
  CInterface interface = CInterfaceLocator::getInerface();
  while (toControl.GetCurrActionPoints() > 0) {
    int res = showPosibilities(toControl);
    switch (res) {
      case 1:
        move(toControl);
        break;
      case 2:
        attack(toControl);
        break;
    }
  }
  interface.Message("End of your turn");
}
std::shared_ptr<CControler> CPlayerController::Create() { return std::make_shared<CPlayerController>(); }
void CPlayerController::AttachToEntity(std::weak_ptr<CEntity> entity) { m_Entity = entity; }

int CPlayerController::showPosibilities(CEntity& toControl) {
  std::string actions = "Choose what do you want to do.\n1) move cost: ";
  actions += std::to_string(toControl.GetMovementCost()) += "\n";
  actions += "2)attack cost: ";
  actions += std::to_string(toControl.GetAttackCost()) += "\n";
  actions += "Current action points: ";
  actions += std::to_string(toControl.GetCurrActionPoints());
  CInterface interface = CInterfaceLocator::getInerface();
  bool state = false;
  while (!state) {
    int res = interface.PromtWithMessage<int>(actions);
    if (res > 0 && res <= 2) {
      state = true;
      return res;
    } else {
      interface.Message("Wrong options, choose again!");
      state = false;
    }
  }
  return 0;
}
bool CPlayerController::move(CEntity& toControl) {
  CInterface interface = CInterfaceLocator::getInerface();
  int x = interface.PromtWithMessage<int>("where do you want to move on X");
  int y = interface.PromtWithMessage<int>("where do you want to move on y");
  if (!toControl.Move(x, y)) {
    interface.Message("You tried to move too far");
    return false;
  }
  return true;
}
bool CPlayerController::attack(CEntity& toControl) {
  CInterface interface = CInterfaceLocator::getInerface();
  auto posTargets = toControl.getEntitiesInRange(5);
  std::string message = "who do you want to attack?\n";
  int j = 0;
  for (size_t i = 0; i < posTargets.size(); ++i, ++j) {
    message += std::to_string(j + 1);
    message += ") ";
    message += posTargets.at(i)->GetName();
    message += "\n";
    interface.Message(message);
  }
  return false;
}
