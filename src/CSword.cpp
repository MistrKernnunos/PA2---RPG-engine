//
// Created by machavi on 6/4/21.
//

#include "CSword.h"
bool CSword::Defense(std::shared_ptr<CEntity> user) { return false; }
bool CSword::Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) { return false; }
bool CSword::Attack(CEntity& toAttack, CEntity& user) const {
  int damage = (GetAttackPower() + user.GetAttackPower()) * user.GetLevel();
  toAttack.Attacked(damage);
}
std::unique_ptr<CWeapon> CSword::Create() { return std::make_unique<CSword>(); }
std::string CSword::PrintToString() {
  std::string message = "Name: ";
  message += GetName();
  message += "\n  Strength: ";
  message += std::to_string(GetAttackPower());
  message += "\n";
  message += "  range: ";
  message += std::to_string(GetRange());
}
