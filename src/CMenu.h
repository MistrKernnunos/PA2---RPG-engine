//
// Created by machavi on 5/7/21.
//

#pragma once
#include "CInterface.h"
#include "CPlayer.h"
#include "CGame.h"

class CMenu {
 public:
  CMenu(CInterface& interface) : m_Interface(interface) {}

  bool IsReady();

  bool RunMenu(CGame & game);

 private:
  bool createPlayer();
  bool loadGame();
  bool loadMap();
  bool createGame();
  bool quit();
  CInterface& m_Interface;
};