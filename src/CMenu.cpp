//
// Created by machavi on 5/7/21.
//

#include "CMenu.h"

#include "CInterface.h"
#include "CPlayerCreator.h"
bool CMenu::RunMenu(CGame& game) {
  std::string message = "1) load game\n2) create game\n3) quit";
  bool state = false;

  while (!state) {
    int res = m_Interface.Chooser(message, 3);
    switch (res) {
      case 1:
        state = loadMap(game);
        break;
      case 2:
        state = createGame(game);
        break;
      case 3:
        return false;
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
bool CMenu::createGame(CGame& game) {
  m_Interface.Message("First you need to create your entity");
  CPlayerCreator creator;
  auto player = creator.Create();
  m_Interface.Message("Then you need to load map");
  if (!loadMap(game)) {
    return false;
  }
  return game.SpawnPlayer(player);
}
