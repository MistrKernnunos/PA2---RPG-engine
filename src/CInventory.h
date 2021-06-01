//
// Created by machavi on 5/9/21.
//

#pragma once
#include <memory>
#include <vector>

#include "CFileLoaderIterator.h"
#include "CItem.h"
#include "CItemLoader.h"

class CInventory {
 public:
  CInventory() = default;
  CInventory(size_t invSize) : m_Size(invSize){};

  /**
   * transfers item from one inventory to another, checks wheather the item will
   * fit inside
   * @param from inventory from which to take the item
   * @param index index of the item in the vector
   * @return true if the transfer succeeded, false if the item is too big
   */
  bool insert(CInventory& from, size_t index);

  /**
   * removes the item from inventory
   * @param index index of the item in the vector
   * @return
   */
  bool drop(size_t index);

  /**
   * returns reference to the inventory array
   * @return const reference to inventory array
   */
  const std::vector<std::unique_ptr<CItem>>& getInventory();

  /**
   * loads inventory from xml file
   * @param it iterator to inventory node
   * @return true if successful, false if not
   */
  bool Load(CFileLoaderIt it);

 private:
  size_t m_Size = 0;
  std::vector<std::unique_ptr<CItem>> m_Inventory;
};
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
