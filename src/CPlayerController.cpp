//
// Created by machavi on 6/2/21.
//

#include "CPlayerController.h"

#include "CEntity.h"
#include "CInterfaceLocator.h"
#include "CPlayer.h"
void CPlayerController::Control(CEntity& toControl) {
  CInterface interface = CInterfaceLocator::getInerface();
  int res = showPosibilities();
  if (res == 1) {
    int x = interface.PromtWithMessage<int>("where do you want to move on X");
    int y = interface.PromtWithMessage<int>("where do you want to move on y");
    if (!toControl.Move(x, y)) {
      interface.Message("You tried to move too far");
    }
  } else if (res == 2) {
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
  }
}
std::shared_ptr<CControler> CPlayerController::Create() { return std::make_shared<CPlayerController>(); }
void CPlayerController::AttachToEntity(std::weak_ptr<CEntity> entity) { m_Entity = entity; }

int CPlayerController::showPosibilities() {
  std::string actions = "Choose what do you want to do.\n  1) move";
  CInterface interface = CInterfaceLocator::getInerface();
  bool state = false;
  while (!state) {
    int res = interface.PromtWithMessage<int>(actions);
    if (res > 0 && res <= 2) {
      state = true;
      return res;
    }
    interface.Message("Wrong options, choose again!");
  }
  return 0;
}
