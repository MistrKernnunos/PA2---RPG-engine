//
// Created by machavi on 5/7/21.
//
#pragma once
#include <memory>
#include <vector>

#include "CEntity.h"
#include "CInterface.h"
#include "CRoom.h"


class CGame {
 public:
  CGame(const CInterface &interface) : m_Interface(interface){};
  CGame(const CGame &) = delete;
  CGame &operator=(const CGame &) = delete;

  bool LoadGame();

  bool LoadMap();

  bool Save() const;

  bool Start();

  bool IsInitialized() const;

  std::shared_ptr<CEntity> GetClosesEntityTo(const int x, const int y);
  std::pair<int, int> GetPosition(CEntity &entity);

 private:
  CInterface m_Interface;
  std::vector<std::shared_ptr<CRoom>> m_Rooms;
};
