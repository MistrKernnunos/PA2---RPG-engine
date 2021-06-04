//
// Created by machavi on 6/1/21.
//
#pragma once
#include <string>
#include <vector>

#include "CFactory.h"
#include "CFileLoaderIterator.h"
#include "CWeapon.h"

class CWeaponLoader {
 public:
  CWeaponLoader();
  std::vector<std::unique_ptr<CWeapon>> LoadWeapons(CFileLoaderIt iterator);

 private:
  CFactory<CWeapon, std::string, std::unique_ptr<CWeapon>> m_ItemFactory;
};
