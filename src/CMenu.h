//
// Created by machavi on 5/7/21.
//

#pragma once
#include "CGame.h"
#include "CInterface.h"

class CMenu {
 public:
  CMenu(CInterface& interface) : m_Interface(interface) {}

  /**
   * runs the menu
   * @param game game to control with menu
   * @return true if successful, false if not or quit
   */
  bool RunMenu(CGame& game);

 private:
  bool loadMap(CGame& game);
  bool createGame(CGame& game);
  CInterface& m_Interface;
};
