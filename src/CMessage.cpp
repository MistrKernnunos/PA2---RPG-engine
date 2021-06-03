//
// Created by machavi on 6/3/21.
//

#include "CMessage.h"

MessageType CMessage::GetType() const { return m_Type; }
const std::vector<std::pair<std::string, std::string>>& CMessage::GetStringMessages() const { return m_StringMessages; }
const std::vector<std::pair<std::string, int>>& CMessage::GetIntMessages() const { return m_IntMessages; }

void CMessage::AttachPayload(const std::string& key, int message) { m_IntMessages.emplace_back(key, message); }

void CMessage::AttachPayload(const std::string& key, const std::string& message) {
  m_StringMessages.emplace_back(key, message);
}
const std::pair<int, int> CMessage::GetMessagesTypes() const {
  auto types = std::make_pair(m_StringMessages.size(), m_IntMessages.size());
  return types;
}
