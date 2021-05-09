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
   * applies defensive action of the weapon
   * @param user entity which uses the weapon
   * @return true if it was successful, false if not (not enough Action points,
   * does not have defense mechanism)
   */
  virtual bool Defense(std::shared_ptr<CEntity> user) = 0;

  /**
   * performs effect of this item
   * @param toEffect entity which this item effects
   * @param user entity which uses this item
   * @return if the effect was used successfully
   */
  virtual bool Effect(std::shared_ptr<CEntity> toEffect,
                      std::shared_ptr<CEntity> user) = 0;

  /**
   * performs attack with this weapon
   * @param toEffect entity to attack
   * @param user entity which uses this weapon
   * @return true if the attack was used successfully
   */
  virtual bool Attack(std::shared_ptr<CEntity> toAttack,
                      std::shared_ptr<CEntity> user) = 0;

 private:
  unsigned int m_Range;
  unsigned int m_AttackPower;
  unsigned int m_DefensePower;
};