//
// Created by machavi on 6/3/21.
//
#pragma once
#include "CEntity.h"
#include "CGame.h"
#include "CMessage.h"
#include "map"

class CMessagingService {
 public:
  CMessagingService() = default;

  bool Subscribe(int id, std::shared_ptr<CEntity> entity);
  bool Unsubcribe(int id);
  bool SendMessage(const CMessage& message);

 private:
  std::map<int, std::shared_ptr<CEntity>> m_SubscribedEntities;
  CGame m_Game;
};