//
// Created by machavi on 6/1/21.
//
#pragma once
#include <memory>
#include <ostream>

#include "CEntity.h"
#include "CFileLoaderIterator.h"
#include "CItem.h"

class CHealthPotion : public CItem {
 public:
  CHealthPotion() = default;
  ~CHealthPotion() = default;

  /**
   * heals player by healing strength
   * @param toEffect player to effect
   * @param user the user
   * @return true if not already fully health
   */
  bool Effect(CEntity& toEffect, CEntity& user) override;
  /**
   * saves potion to file
   * @param iterator where to save
   * @return true if successful
   */
  bool Save(CFileLoaderIt iterator) const override;

  /**
   * creates blank health potion
   * @return uniq pointer
   */
  static std::unique_ptr<CItem> Create();
  /**
   * loads health potion from file
   * @param iterator from where to load
   * @return true if successful
   */
  bool Load(CFileLoaderIt iterator);

  /**
   * outputs the info about the potion, used in player communication
   * @return info about the potion in string
   */
  std::string PrintToString() override;

 private:
  std::ostream& print(std::ostream& out) const override;

  int m_HealingStrength = 0;
};
