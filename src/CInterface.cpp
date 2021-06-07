//
// Created by machavi on 5/7/21.
//
#include "CInterface.h"
void CInterface::Message(const std::string& message) const { m_Out << message << std::endl; }

int CInterface::Chooser(const std::string& message, int numberOfChoices) {
  bool state = false;
  while (!state) {
    int res = PromtWithMessage<int>(message);
    if (res > 0 && res <= numberOfChoices) {
      state = true;
      return res;
    } else {
      Message("Wrong options, choose again!");
      state = false;
    }
  }
  return 0;
}
