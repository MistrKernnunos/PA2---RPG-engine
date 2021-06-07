//
// Created by machavi on 5/9/21.
//

#pragma once
#include <memory>
#include <vector>

#include "CFileLoaderIterator.h"
#include "CItem.h"
#include "CWeapon.h"

enum invType { WEAPON, ITEM, BOTH };
class CInventory {
 public:
  CInventory() = default;
  explicit CInventory(size_t invSize);

  /**
   * transfers item from one inventory to another, checks wheather the item will
   * fit inside
   * @param from inventory from which to take the item
   * @param index index of the item in the vector
   * @return true if the transfer succeeded, false if the item is too big
   */
  bool insert(CInventory& from, size_t index, invType type);

  /**
   * removes the item from inventory
   * @param index index of the item in the vector
   * @return
   */
  bool drop(size_t index, invType type);

  /**
   * returns reference to the inventory array
   * @return const reference to inventory array
   */
  const std::vector<std::unique_ptr<CItem>>& GetItemInventory() const;
  const std::vector<std::unique_ptr<CWeapon>>& GetWeaponInventory() const;

  std::unique_ptr<CItem> TakeItem(size_t index);
  std::unique_ptr<CWeapon> TakeWeapon(size_t index);

  /**
   * loads inventory from xml file
   * @param it iterator to inventory node
   * @return true if successful, false if not
   */
  bool Load(CFileLoaderIt it);

  /**
   * saves inventory to it
   * @param it iterator to where to save it
   * @return true if successful, false if not
   */
  bool Save(CFileLoaderIt it) const;

 private:
  size_t m_Size = 0;
  size_t m_CurrSize = 0;
  std::vector<std::unique_ptr<CItem>> m_Inventory;
  std::vector<std::unique_ptr<CWeapon>> m_WeaponInventory;

  bool saveItems(CFileLoaderIt it) const;
  bool saveWeapons(CFileLoaderIt it) const;
  bool erase(size_t index, invType type);
};
