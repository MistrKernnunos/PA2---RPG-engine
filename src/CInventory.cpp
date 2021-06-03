//
// Created by machavi on 5/9/21.
//
#include "CInventory.h"
bool CInventory::insert(CInventory& from, size_t index) { return false; }
const std::vector<std::unique_ptr<CItem>>& CInventory::getInventory() { return m_Inventory; }
bool CInventory::drop(size_t index) { return false; }

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
  it.Next();
  it.Next();
  CItemLoader itemLoader;
  m_Inventory = itemLoader.LoadItems(it);
  return true;
}
