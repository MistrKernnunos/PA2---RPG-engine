//
// Created by machavi on 5/7/21.
//

#pragma once
#include "CGame.h"
#include "CInterface.h"
#include "CPlayer.h"

class CMenu {
 public:
  CMenu(CInterface& interface) : m_Interface(interface) {}

  bool IsReady();

  bool RunMenu(CGame& game);

 private:
  //  bool createPlayer();
//  bool loadGame(CGame& game);
  //  bool startGame(CGame & game);
    bool loadMap(CGame & game);
  //  bool createGame(CGame & game);
  //  bool quit();
  CInterface& m_Interface;
};

bool CMenu::RunMenu(CGame& game) {
  std::string message = "1) load map";
  bool state = false;

  while (!state) {
    int res = m_Interface.PromtWithMessage<int>(message);
    if (res > 0 && res <= 6) {
      state = true;
    }
    switch (res) {
      case 1:
        loadMap(game);
        break;
      default:
        m_Interface.Message("Wrong options, choose again!");
        break;
    }
  }
  return true;
}

bool CMenu::loadMap(CGame& game) {
  std::string filePath =
      m_Interface.PromtWithMessage<std::string>("Enter path to map file:");
}