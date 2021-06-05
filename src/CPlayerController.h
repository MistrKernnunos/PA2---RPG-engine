//
// Created by machavi on 6/2/21.
//
#pragma once
#include <memory>
#include <vector>

#include "CControler.h"
#include "CInterface.h"
#include "CWeapon.h"
class CPlayer;

class CPlayerController : public CControler {
 public:
  CPlayerController() = default;

  void Control(CEntity& toControl) override;
  static std::shared_ptr<CControler> Create();
  void AttachToEntity(std::weak_ptr<CEntity> entity) override;

 private:
  size_t chooseEntityToAttack(CEntity& toControl, std::vector<std::shared_ptr<CEntity>>& entitiesToAttack);
  int showActions(CEntity& toControl);
  void move(CEntity& toControl);
  void attack(CEntity& toControl);
  size_t chooseWeapon(CEntity& toControl);
};
