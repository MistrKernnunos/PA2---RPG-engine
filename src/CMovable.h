//
// Created by machavi on 5/7/21.
//
#pragma once
#include "CEntity.h"
class CMovable : public CEntity {
 public:
  CMovable() = default;
  /**
   *moves entity by x and y
   * @param x
   * @param y
   * @return
   */
  virtual bool move(const int x, const int y) = 0;

 protected:
  int m_Movement;
};
