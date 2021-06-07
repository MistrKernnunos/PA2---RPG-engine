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
  virtual bool Control(CEntity& toControl) = 0;


 protected:
};
