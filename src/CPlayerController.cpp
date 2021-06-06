//
// Created by machavi on 6/2/21.
//

#include "CPlayerController.h"

#include "CEntity.h"
#include "CInterfaceLocator.h"
#include "CItem.h"
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
        inventory(toControl);
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
    if (res > 0 && res <= 3) {
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
    interface.Message("No weapon chosen");
    return;
  }
  weaponIndex--;
  auto entities = toControl.GetEntitiesInRange(inventory.GetWeaponInventory().at(weaponIndex)->GetRange());
  size_t entityIndex = chooseEntityToAttack(toControl, entities);
  if (entityIndex == 0) {
    interface.Message("No entity chosen");
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
  size_t res = interface.PromtWithMessage<size_t>(message);
  if (res >= entitiesToAttack.size()) res = 0;
  return res;
}
size_t CPlayerController::chooseWeapon(CEntity& toControl) { return chooseItem(toControl, WEAPON); }
void CPlayerController::inventory(CEntity& toControl) {
  size_t index = chooseItem(toControl, ITEM);
  if (index != 0) {
    useItem(toControl, index);
  }
}
size_t CPlayerController::chooseItem(CEntity& toControl, invType type = ITEM) {
  CInterface interface = CInterfaceLocator::getInerface();
  const CInventory& inv(toControl.GetInventory());
  size_t j = 1;
  std::string message = "Choose item to use\n0) no item\n";
  if (type == ITEM || type == BOTH) {
    for (auto& elem : inv.GetItemInventory()) {
      message += std::to_string(j);
      message += ") ";
      message += elem->PrintToString();
      message += "\n";
      j++;
    }
  }
  if (type == WEAPON || type == BOTH) {
    for (auto& elem : inv.GetWeaponInventory()) {
      message += std::to_string(j);
      message += ") ";
      message += elem->PrintToString();
      message += "\n";
      j++;
    }
  }
  size_t res = interface.PromtWithMessage<size_t>(message);
  if (res >= j) res = 0;
  return res;
}
bool CPlayerController::useItem(CEntity& toControl, size_t index) {
  CInventory& inv(toControl.GetEditableInventory());
  index--;
  auto item = inv.TakeItem(index);
  return item->Effect(toControl, toControl);
}
void CPlayerController::loot(CEntity& toControl) {
  auto lootable = toControl.GetLootableEntities();
  CInterface interface = CInterfaceLocator::getInerface();
  if (lootable.size() == 0) {
    interface.Message("No entities to loot");
    return;
  }
  size_t choice = chooseEntityToLoot(lootable, toControl);
  if (choice == 0) {
    interface.Message("No entity chosen");
    return;
  }
  choice--;
  size_t itemIndex = chooseItem(*lootable.at(choice), ITEM);
  if (choice == 0) {
    interface.Message("No item chosen");
    return;
  }
  itemIndex--;
  CInventory& inv(lootable.at(choice)->GetEditableInventory());
  if (itemIndex >= inv.GetItemInventory().size()) {
    itemIndex -= inv.GetItemInventory().size();
    toControl.GetEditableInventory().insert(lootable.at(choice)->GetEditableInventory(), itemIndex, WEAPON);
  }
  toControl.GetEditableInventory().insert(lootable.at(choice)->GetEditableInventory(), itemIndex, ITEM);
}
size_t CPlayerController::chooseEntityToLoot(std::vector<std::shared_ptr<CEntity>>& entities, CEntity& toControl) {
  CInterface interface = CInterfaceLocator::getInerface();
  std::string message = "Choose who do you want to loot!\n";
  CCoordinates myPos = toControl.GetCoordinates();
  size_t j = 1;
  message += "0) nobody\n";
  for (auto& elem : entities) {
    message += std::to_string(j + 1);
    message += ") ";
    message += elem->GetName();
    message += "\n";
    message += "  position relative to you:";
    CCoordinates coor = elem->GetCoordinates();
    message += "  X: ";
    message += std::to_string(coor.X() - myPos.X());
    message += " Y: ";
    message += std::to_string(coor.Y() - myPos.Y());
    message += "\n";
    j++;
  }
  size_t res = interface.PromtWithMessage<size_t>(message);
  if (res >= j) res = 0;
  return res;
}
