//
// Created by machavi on 5/7/21.
//

#include "CMenu.h"
#include "CInterface.h"
bool CMenu::RunMenu(CGame& game) {
  std::string message = "1) load map";
  bool state = false;

  while (!state) {
    int res = m_Interface.PromtWithMessage<int>(message);
    if (res > 0 && res <= 1) {
      state = true;
    }
    switch (res) {
      case 1:
        state = loadMap(game);
        break;
      default:
        m_Interface.Message("Wrong options, choose again!");
        break;
    }
  }
  return true;
}

bool CMenu::loadMap(CGame& game) {
  std::string filePath = m_Interface.PromtWithMessage<std::string>("Enter path to map file:");
  game.IsInitialized();
  try {
    game.LoadMap(filePath);
  } catch (std::exception& error) {
    game.Erase();
#ifdef DEBUG
    m_Interface.Print(error.what());
#endif
    m_Interface.Message("An error occurred during map loading. Returning to menu");
    return false;
  }
  return true;
}