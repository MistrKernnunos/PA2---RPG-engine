//
// Created by machavi on 6/2/21.
//
#pragma once
#include <memory>

#include "CControler.h"
#include "CInterface.h"
class CPlayer;

class CPlayerController : public CControler {
 public:
  CPlayerController() = default;

  void Control(CEntity& toControl) override;
  static std::shared_ptr<CControler> Create();
  void AttachToEntity(std::weak_ptr<CEntity> entity) override;

 private:
  int showPosibilities();
};
