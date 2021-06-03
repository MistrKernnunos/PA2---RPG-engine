//
// Created by machavi on 6/3/21.
//

#include "CMessagingService.h"
bool CMessagingService::Subscribe(int id, std::shared_ptr<CEntity> entity) {
  auto res = m_SubscribedEntities.insert(std::make_pair(id, entity));
  return res.second;
}
bool CMessagingService::Unsubcribe(int id) {
  if (m_SubscribedEntities.count(id) == 1) {
    m_SubscribedEntities.erase(id);
    return true;
  }
  return false;
}

bool CMessagingService::SendMessage(const CMessage &message) {
  switch (message.GetType()) {
    case Attack:

      break;
    case AoeAttack:
      break;
    case InfoMessage:
      break;
    case Render:
      m_Game.Render();
      break;
  }
  return false;
}