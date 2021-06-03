//
// Created by machavi on 6/3/21.
//
#pragma once
#include <string>
#include <vector>
#include "CGame.h"

enum MessageType { Attack, AoeAttack, InfoMessage, Render };
class CMessage {
 public:
  CMessage(int reciever, MessageType type);

  void AttachPayload(const std::string& key, const std::string& message);
  void AttachPayload(const std::string& key, int message);

  MessageType GetType() const;
  const std::vector<std::pair<std::string, std::string>>& GetStringMessages() const;
  const std::vector<std::pair<std::string, int>>& GetIntMessages() const;

  const std::pair<int, int> GetMessagesTypes() const;

 private:
  MessageType m_Type;
  std::vector<std::pair<std::string, std::string>> m_StringMessages;
  std::vector<std::pair<std::string, int>> m_IntMessages;
};
