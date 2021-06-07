//
// Created by machavi on 6/7/21.
//
#pragma once
#include <functional>
#include <map>
#include <memory>

#include "CPlayer.h"

class CPlayerCreator {
 public:
  CPlayerCreator();
  std::shared_ptr<CEntity> Create();

 private:
  int m_Points = 30;
  std::shared_ptr<CEntity> m_Player;
  std::map<std::string, std::reference_wrapper<int>> m_Stats;
};
