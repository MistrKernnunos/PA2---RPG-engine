//
// Created by machavi on 5/7/21.
//
#pragma once
#include "CEntity.h"
class CMovable : public CEntity {
 public:
  CMovable(const string& name, int height, int width, size_t invSize,
           int maxHealth, int nextLevCoef = 5, int defence = 0, int attack = 0,
           int movement = 1)
      : CEntity(name, height, width, invSize, maxHealth, nextLevCoef, defence,
                attack),
        m_Movement(movement) {}
  /**
   *moves entity by x and y
   * @param x
   * @param y
   * @return
   */
  virtual bool move(const int x, const int y) = 0;

 private:
  int m_Movement;
};
