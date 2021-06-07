//
// Created by machavi on 5/7/21.
//

#pragma once
#include "CGame.h"
#include "CInterface.h"

class CMenu {
 public:
  CMenu(CInterface& interface) : m_Interface(interface) {}

  bool IsReady();

  bool RunMenu(CGame& game);

 private:
  //  bool createPlayer();
  //  bool loadGame(CGame& game);
  //  bool startGame(CGame & game);
  bool loadMap(CGame& game);
    bool createGame(CGame & game);
  //  bool quit();
  CInterface& m_Interface;
};
