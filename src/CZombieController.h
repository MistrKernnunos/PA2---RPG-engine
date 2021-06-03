//
// Created by machavi on 6/2/21.
//

#include <memory>

#include "CControler.h"
class CZombieController : public CControler {
 public:
  ~CZombieController() override = default;
  void Control(CEntity& toControl) override;
  static std::shared_ptr<CControler> Create();
  void AttachToEntity(std::weak_ptr<CEntity> entity) override;
};
