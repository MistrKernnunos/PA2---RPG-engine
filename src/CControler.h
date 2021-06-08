//
// Created by machavi on 6/2/21.
//
#pragma once
class CEntity;
#include <memory>

class CControler {
 public:

  CControler() = default;
  virtual ~CControler() = default;
  /**
   * function to start control of Entity
   * @param toControl entity to control
   * @return false if entity wants to end the game
   */
  virtual bool Control(CEntity& toControl) = 0;


 protected:
};
