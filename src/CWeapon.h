//
// Created by machavi on 5/7/21.
//
#include <memory>

#include "CItem.h"

#pragma once

class CWeapon : public CItem {
 public:
  CWeapon(const string &name, const size_t size, unsigned int range,
          unsigned int attackPower, unsigned int defensePower)
      : CItem(name, size),
        m_Range(range),
        m_AttackPower(attackPower),
        m_DefensePower(defensePower) {}

  /**
   * applies defensife action of the weapon
   * @param user entity which uses the weapon
   * @return true if it was succesful, false if not (not enough Action points,
   * does not have defense mechanism)
   */
  virtual bool Defense(std::shared_ptr<CEntity> user) = 0;

 private:
  unsigned int m_Range;
  unsigned int m_AttackPower;
  unsigned int m_DefensePower;
};