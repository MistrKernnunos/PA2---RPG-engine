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

  bool insert(std::unique_ptr<CItem>& item);
  bool insert(std::unique_ptr<CWeapon>& weapon);

  /**
   * returns reference to the inventory array
   * @return const reference to inventory array
   */
  const std::vector<std::unique_ptr<CItem>>& GetItemInventory() const;
  /**
   * returns reference to the weapon array
   * @return const reference to inventory array
   */
  const std::vector<std::unique_ptr<CWeapon>>& GetWeaponInventory() const;

  /**
   * takes item from inventory
   * @param index of the item
   * @return uniq ptr to item
   */
  std::unique_ptr<CItem> TakeItem(size_t index);
  /**
   * takes weapon from inventory
   * @param index of the weapon
   * @return uniq ptr to weapon
   */
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

  /**
   * utility function to save items
   * @param it where to save them
   * @return true if successfully
   */
  bool saveItems(CFileLoaderIt it) const;
  /**
   * utility function to save weapons
   * @param it where to save them
   * @return true if successfully
   */
  bool saveWeapons(CFileLoaderIt it) const;
  /**
   * erases item from inventory, does not decrease curr Size
   * @param index to the item
   * @param type type of the item
   * @return true if successful
   */
  bool erase(size_t index, invType type);
};
