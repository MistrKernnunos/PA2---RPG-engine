//
// Created by machavi on 6/4/21.
//

#include "CSword.h"
bool CSword::Defense(std::shared_ptr<CEntity> user) { return false; }
bool CSword::Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) { return false; }
bool CSword::Attack(std::shared_ptr<CEntity> toAttack, std::shared_ptr<CEntity> user) { return false; }
std::unique_ptr<CWeapon> CSword::Create() { return std::make_unique<CSword>(); }
