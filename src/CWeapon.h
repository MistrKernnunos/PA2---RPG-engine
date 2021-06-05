//
// Created by machavi on 5/7/21.
//
#pragma once
#include <memory>
#include <ostream>

#include "CFileLoaderIterator.h"
class CEntity;

class CWeapon {
 public:
  CWeapon() = default;

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
  virtual bool Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) = 0;

  /**
   * performs attack with this weapon
   * @param toEffect entity to attack
   * @param user entity which uses this weapon
   * @return true if the attack was used successfully
   */
  virtual bool Attack(CEntity& toAttack, CEntity& user) const = 0;

  bool Load(CFileLoaderIt it);

  friend std::ostream& operator<<(std::ostream& os, const CWeapon& weapon);

  const std::string& GetName() const;
  int GetRange() const;
  int GetAttackPower() const;
  int GetDefensePower() const;
  size_t GetSize() const;

 private:
  std::string m_Name;
  int m_Range = 0;
  int m_AttackPower = 0;
  int m_DefensePower = 0;
  size_t m_Size = 0;
};