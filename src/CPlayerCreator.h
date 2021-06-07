//
// Created by machavi on 6/7/21.
//
#pragma once
#include <functional>
#include <map>
#include <memory>
class CEntity;

class CPlayerCreator {
 public:
  CPlayerCreator();
  ~CPlayerCreator() = default;
  std::shared_ptr<CEntity> Create();

 private:
  void chooseProperties();

  std::shared_ptr<CEntity> m_Player;
  std::map<std::string, std::reference_wrapper<int>> m_Stats;
};
