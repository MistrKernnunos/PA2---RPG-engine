//
// Created by machavi on 6/2/21.
//
#pragma once
#include <memory>
#include <vector>

#include "CControler.h"
#include "CInterface.h"
#include "CInventory.h"
#include "CWeapon.h"
class CPlayer;

class CPlayerController : public CControler {
 public:
  CPlayerController() = default;

  bool Control(CEntity& toControl) override;
  static std::shared_ptr<CControler> Create();

 private:
  size_t chooseEntityToAttack(CEntity& toControl, std::vector<std::shared_ptr<CEntity>>& entitiesToAttack);
  int showActions(CEntity& toControl);
  void move(CEntity& toControl);
  void attack(CEntity& toControl);
  size_t chooseWeapon(CEntity& toControl);
  void inventory(CEntity& toControl);
  size_t chooseItem(CEntity& toControl, invType type);
  bool useItem(CEntity& toControl, size_t index);
  void loot(CEntity& toControl);
  size_t chooseEntityToLoot(std::vector<std::shared_ptr<CEntity>>& entities, CEntity& toControl);
  void dropItem(CEntity & toControl,size_t index);
};
