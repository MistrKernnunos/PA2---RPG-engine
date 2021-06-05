//
// Created by machavi on 6/2/21.
//

#include "CPlayerController.h"

#include "CEntity.h"
#include "CInterfaceLocator.h"
#include "CPlayer.h"
void CPlayerController::Control(CEntity& toControl) {
  CInterface interface = CInterfaceLocator::getInerface();
  while (toControl.GetCurrActionPoints() > 0 && toControl.GetState() == ALIVE) {
    int res = showActions(toControl);
    switch (res) {
      case 1:
        move(toControl);
        break;
      case 2:
        attack(toControl);
        break;
      case 3:
        // inventory
        break;
      case 4:
        // loot
        break;
      default:
        interface.Message("Wrong option,choose again.");
        break;
    }
  }
  interface.Message("End of your turn");
}
std::shared_ptr<CControler> CPlayerController::Create() { return std::make_shared<CPlayerController>(); }
void CPlayerController::AttachToEntity(std::weak_ptr<CEntity> entity) { m_Entity = entity; }

int CPlayerController::showActions(CEntity& toControl) {
  std::string actions = "Choose what do you want to do.\n1) move cost: ";
  actions += std::to_string(toControl.GetMovementCost()) += "\n";
  actions += "2)attack cost: ";
  actions += std::to_string(toControl.GetAttackCost()) += "\n";
  actions += "Current action points: ";
  actions += std::to_string(toControl.GetCurrActionPoints());
  actions += " Current health: ";
  actions += std::to_string(toControl.GetHealth());

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
void CPlayerController::move(CEntity& toControl) {
  CInterface interface = CInterfaceLocator::getInerface();
  int x = interface.PromtWithMessage<int>("where do you want to move on X");
  int y = interface.PromtWithMessage<int>("where do you want to move on y");
  if (!toControl.Move(x, y)) {
    interface.Message("You tried to move too far");
  }
}
void CPlayerController::attack(CEntity& toControl) {
  CInterface interface = CInterfaceLocator::getInerface();
  const CInventory& inventory(toControl.GetInventory());
  size_t weaponIndex = chooseWeapon(toControl);
  if (weaponIndex == 0) {
    return;
  }
  if (weaponIndex < 0 || weaponIndex > inventory.GetWeaponInventory().size()) {
    interface.Message("No weapon under this number");
    return;
  }
  weaponIndex--;
  auto entities = toControl.getEntitiesInRange(inventory.GetWeaponInventory().at(weaponIndex)->GetRange());
  size_t entityIndex = chooseEntityToAttack(toControl, entities);
  if (entityIndex == 0) {
    return;
  }
  if (entityIndex < 0 || entityIndex > entities.size()) {
    interface.Message("No entity under this number");
    return;
  }
  entityIndex--;
  if (!toControl.Attack(*entities.at(entityIndex), *inventory.GetWeaponInventory().at(weaponIndex))) {
    interface.Message("Attack failed");
  }
}
size_t CPlayerController::chooseEntityToAttack(CEntity& toControl,
                                               std::vector<std::shared_ptr<CEntity>>& entitiesToAttack) {
  CInterface interface = CInterfaceLocator::getInerface();
  CCoordinates myPos = toControl.GetCoordinates();
  std::string message;
  message += "Choose who do you want to attack!\n";
  message += "0) nobody\n";
  for (size_t i = 0; i < entitiesToAttack.size(); ++i) {
    message += std::to_string(i + 1);
    message += ") ";
    message += entitiesToAttack.at(i)->GetName();
    message += "\n";
    message += "  health:";
    message += std::to_string(entitiesToAttack.at(i)->GetHealth());
    message += "\n";
    message += "  position relative to you:";
    CCoordinates coor = entitiesToAttack.at(i)->GetCoordinates();
    message += "  X: ";
    message += std::to_string(coor.X() - myPos.X());
    message += " Y: ";
    message += std::to_string(coor.Y() - myPos.Y());
  }
  return interface.PromtWithMessage<size_t>(message);
}
size_t CPlayerController::chooseWeapon(CEntity& toControl) {
  const CInventory& inv(toControl.GetInventory());
  size_t size = inv.GetWeaponInventory().size();
  CInterface interface = CInterfaceLocator::getInerface();
  std::string message = "Choose weapon to use\n 0) no weapon\n";
  for (size_t i = 0; i < size; ++i) {
    message += " ";
    message += std::to_string(i + 1);
    message += ") ";
    message += inv.GetWeaponInventory().at(i)->GetName();
    message += "\n";
    message += "  power: ";
    message += std::to_string(inv.GetWeaponInventory().at(i)->GetAttackPower());
    message += "\n";
    message += "  range: ";
    message += std::to_string(inv.GetWeaponInventory().at(i)->GetRange());
  }
  return interface.PromtWithMessage<size_t>(message);
}
