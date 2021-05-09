//
// Created by machavi on 5/7/21.
//
#include <vector>

#include "CEntity.h"
#include "CInterface.h"
#include "CRoom.h"

#pragma once

class CGame {
 public:
  CGame(const CInterface &interface) : m_Interface(interface){};
  CGame(const CGame &) = delete;
  operator=(const CGame &) = delete;

  bool Load();

  bool Save() const;

  bool Start();

  bool IsInitialized() const;


 private:
  CInterface m_Interface;
  std::vector<std::shared_ptr<CRoom>> m_Rooms;
};
