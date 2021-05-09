//
// Created by machavi on 5/9/21.
//
#include <memory>
#include <vector>

#include "CItem.h"

#pragma once

class CInventory {
 public:
  CInventory(size_t invSize) : m_Size(invSize);

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
  const vector<std::unique_ptr<CItem>>& getInventory();

 private:
  size_t m_Size;
  vector<std::unique_ptr<CItem>> m_Inventory
};