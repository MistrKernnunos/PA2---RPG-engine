//
// Created by machavi on 6/4/21.
//

#include "CSword.h"
bool CSword::Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) { return false; }
void CSword::Attack(CEntity& toAttack, CEntity& user) const {
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
  return message;
}
bool CSword::addEntityID(CFileLoaderIt it) const {
  if (it.GetName() != "weapon") {
    return false;
  }
  std::list<std::pair<std::string, std::string>> propList;
  propList.emplace_back("weaponID", "sword");
  return it.AddProperties(propList);
}
