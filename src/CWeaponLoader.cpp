//
// Created by machavi on 6/1/21.
//
#include "CWeaponLoader.h"

#include "CSword.h"

CWeaponLoader::CWeaponLoader() { m_ItemFactory.Register("sword", CSword::Create); }

std::vector<std::unique_ptr<CWeapon>> CWeaponLoader::LoadWeapons(CFileLoaderIt iterator) {
  std::vector<std::unique_ptr<CWeapon>> weapons;
  if (iterator.GetName() != "weapons") {
    throw std::invalid_argument("wrong weapon node");
    return weapons;
  }

  iterator.Child();  // go to weapon node
  iterator.Next();
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    auto prop = iterator.GetProperties();
    if (prop.empty() || prop.size() != 1 || prop.front().first != "weaponID") {
      throw std::invalid_argument("wrong weapon node ");
      return weapons;
    }
    weapons.push_back(m_ItemFactory.createObject(prop.front().second));
    if (!weapons.back()) {
      auto end = weapons.end();
      weapons.erase(--end);
      return weapons;
    }
    if (!weapons.back()->Load(iterator)) {
      weapons.erase(weapons.end() - 1);
      throw std::invalid_argument("error during weapon loading");
      return weapons;
    }

#ifdef DEBUG
    std::cout << *(weapons.back());
    std::cout << std::endl;
#endif
  }
  return weapons;
}