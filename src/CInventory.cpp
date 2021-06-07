//
// Created by machavi on 5/9/21.
//
#include "CInventory.h"

#include "CItem.h"
#include "CItemLoader.h"
#include "CWeaponLoader.h"
bool CInventory::insert(CInventory& from, size_t index, invType type) {
  if (type == ITEM) {
    if (index < from.GetItemInventory().size() && from.GetItemInventory().at(index)->GetSize() + m_CurrSize <= m_Size) {
      auto item = from.TakeItem(index);
      return insert(item);
    }
  } else {
    if (index < from.GetWeaponInventory().size() &&
        from.GetWeaponInventory().at(index)->GetSize() + m_CurrSize <= m_Size) {
      auto item = from.TakeWeapon(index);
      return insert(item);
    }
  }
  return false;
}
const std::vector<std::unique_ptr<CItem>>& CInventory::GetItemInventory() const { return m_Inventory; }
bool CInventory::drop(size_t index, invType type) {
  if (type == ITEM) {
    if (index < m_Inventory.size()) {
      auto it = m_Inventory.begin() + index;
      m_CurrSize -= (*it)->GetSize();
      m_Inventory.erase(it);
      return true;
    }
  } else {
    if (index < m_WeaponInventory.size()) {
      auto it = m_WeaponInventory.begin() + index;
      m_CurrSize -= (*it)->GetSize();
      m_WeaponInventory.erase(it);
      return true;
    }
  }
  return false;
}

bool CInventory::Load(CFileLoaderIt it) {
  if (it.GetName() != "inventory") {
    throw std::invalid_argument("wrong inventory node");
    return false;
  }
  it.Child();
  it.Next();
  if (it.GetName() != "size") {
    throw std::invalid_argument("wrong inventory node");
    return false;
  }
  m_Size = std::stoi(it.GetContent());

  if (!it.Next(2)) return false;
  CItemLoader itemLoader;
  m_Inventory = itemLoader.LoadItems(it);

  if (!it.Next(2)) return false;
  CWeaponLoader weaponLoader;
  m_WeaponInventory = weaponLoader.LoadWeapons(it);
  size_t size = 0;
  for (auto& elem : m_Inventory) {
    size += elem->GetSize();
  }

  for (auto& elem : m_WeaponInventory) {
    size += elem->GetSize();
  }
  if (size > m_Size) {
    throw std::invalid_argument("items and weapons dot fit to inventory");
    return false;
  }
  m_CurrSize = size;

  return true;
}

const std::vector<std::unique_ptr<CWeapon>>& CInventory::GetWeaponInventory() const { return m_WeaponInventory; }

std::unique_ptr<CItem> CInventory::TakeItem(size_t index) {
  std::unique_ptr<CItem> ptr;
  if (index < m_Inventory.size()) {
    ptr.swap(m_Inventory.at(index));
    this->erase(index, ITEM);
    return ptr;
  }
  return ptr;
}

std::unique_ptr<CWeapon> CInventory::TakeWeapon(size_t index) {
  std::unique_ptr<CWeapon> ptr;
  if (index < m_WeaponInventory.size()) {
    ptr.swap(m_WeaponInventory.at(index));
    m_CurrSize -= ptr->GetSize();
    this->erase(index, WEAPON);
    return ptr;
  }
  return ptr;
}

CInventory::CInventory(size_t invSize) : m_Size(invSize) {}
bool CInventory::Save(CFileLoaderIt it) const {
  if (it.GetName() != "inventory") {
    return false;
  }
  if (!it.CreateNewTextChildNode("size", std::to_string(m_Size))) return false;
  if (!it.CreateNewChildNode("items")) return false;
  if (!it.CreateNewChildNode("weapons")) return false;

  it.Child();
  it.Next();
  if (!saveItems(it)) return false;
  it.Next();
  return saveWeapons(it);
}
bool CInventory::saveItems(CFileLoaderIt it) const {
  if (it.GetName() != "items") {
    return false;
  }

  if (m_Inventory.empty()) {
    return true;
  }
  for (size_t i = 0; i < m_Inventory.size(); ++i) {
    it.CreateNewChildNode("item");
  }
  it.Child();
  for (auto& elem : m_Inventory) {
    if (!elem->Save(it)) return false;
    it.Next();
  }
  return true;
}
bool CInventory::saveWeapons(CFileLoaderIt it) const {
  if (it.GetName() != "weapons") {
    return false;
  }
  if (m_WeaponInventory.empty()) {
    return true;
  }
  for (size_t i = 0; i < m_Inventory.size(); ++i) {
    it.CreateNewChildNode("weapon");
  }
  if (!it.Child()) return false;
  for (auto& elem : m_WeaponInventory) {
    if (!elem->Save(it)) {
      return false;
    }
    if (!it.Next()) {
      return false;
    }
  }
  return true;
}
bool CInventory::erase(size_t index, invType type) {
  if (type == ITEM) {
    if (index < m_Inventory.size()) {
      auto it = m_Inventory.begin() + index;
      m_Inventory.erase(it);
    }
  } else {
    if (index < m_WeaponInventory.size()) {
      auto it = m_WeaponInventory.begin() + index;
      m_WeaponInventory.erase(it);
    }
  }
  return false;
}
bool CInventory::insert(std::unique_ptr<CItem>& item) {
  if (item->GetSize() + m_CurrSize <= m_Size) {
    if (item) {
      m_Inventory.resize(m_Inventory.size() + 1);
      m_CurrSize += item->GetSize();
      m_Inventory.back().swap(item);
      return true;
    } else {
      return false;
    }
  }
  return false;
}
bool CInventory::insert(std::unique_ptr<CWeapon>& weapon) {
  if (weapon->GetSize() + m_CurrSize <= m_Size) {
    if (weapon) {
      m_WeaponInventory.resize(m_WeaponInventory.size() + 1);
      m_CurrSize += weapon->GetSize();
      m_WeaponInventory.back().swap(weapon);
      return true;
    } else {
      return false;
    }
  }
  return false;
}
