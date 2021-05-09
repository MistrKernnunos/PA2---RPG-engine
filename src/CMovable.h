//
// Created by machavi on 5/7/21.
//
#include "CEntity.h"
#pragma once
class CMovable : public CEntity {
 public:
  CMovable(const string& name, int height, int width, size_t invSize,
           unsigned int maxHealth, unsigned int nextLevCoef = 5,
           unsigned int defence, unsigned int attack)
      : CEntity(name, height, width, invSize, maxHealth, nextLevCoef, defence,
                attack) {}
  /**
   *moves entity by x and y
   * @param x
   * @param y
   * @return
   */
  virtual bool move(const int x, const int y) = 0;
};
