//
// Created by machavi on 6/7/21.
//

#include "CPlayerCreator.h"

#include <string>

#include "CEntityLoader.h"
#include "CInterfaceLocator.h"
#include "CPlayer.h"

CPlayerCreator::CPlayerCreator() {
  CEntityLoader loader;
  m_Player = loader.CreateEntity("player");
  m_Stats.emplace("attack", m_Player->m_AttackPower);
  m_Stats.emplace("attackCost", m_Player->m_AttackCost);
  m_Stats.emplace("movement", m_Player->m_Movement);
  m_Stats.emplace("movementCost", m_Player->m_MovementCost);
  m_Stats.emplace("maxHealth", m_Player->m_MaxHealth);
  m_Stats.emplace("health", m_Player->m_Health);
  m_Stats.emplace("level", m_Player->m_Level);
  m_Stats.emplace("defense", m_Player->m_DefencePower);
  m_Stats.emplace("defenseCost", m_Player->m_DefenseCost);
  m_Stats.emplace("actionPoints", m_Player->m_ActionPoints);
}
std::shared_ptr<CEntity> CPlayerCreator::Create() {
  CInterface interface = CInterfaceLocator::getInterface();
  m_Player->m_Name = interface.PromtWithMessage<std::string>("What is the player name? ( must be one word)");
  chooseProperties();
  return m_Player;
}
void CPlayerCreator::chooseProperties() {
  auto interface = CInterfaceLocator::getInterface();
  std::string message = "You can choose which property to edit from these: \n";
  message += "edit the properties with command name [value]\nname of property with nothing will reset to zero";
  interface.Message(message);
  std::pair<std::string, int> res;
  while (true) {
    message.clear();
    message += "\t name \t\tcurrent value\n";
    for (auto& elem : m_Stats) {
      message += "\t";
      message += elem.first;
      message += ":\t";
      message += std::to_string(elem.second.get());
      message += "\n";
    }
    message += "q to finish";
    res = interface.PromtWithMessage<std::string, int>(message);
    if (res.first == "q") {
      break;
    }
    if (m_Stats.count(res.first) == 0) {
      interface.Message("\033[101;93m Wrong property\033[0m");
    } else {
      m_Stats.at(res.first).get() = res.second;
    }
  }
}
