#include <iostream>

#include "CFileLoader.h"
#include "CFileLoaderIterator.h"
#include "CInterface.h"
#include "CInterfaceLocator.h"
#include "CMenu.h"
#include "CPlayerCreator.h"
int main() {
  CInterface interface(std::cout, std::cin);
  CInterfaceLocator::provide(&interface);
  CGame game(interface);
  //try catch blok inspired by @David Bernhauer https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/blob/master/src/main.cpp

  try {
    CMenu menu(interface);
    if (menu.RunMenu(game)) {
      if (game.IsInitialized()) {
        game.Start();
      }
    }
  } catch (const std::ios::failure& error) {
    if (std::cin.eof()) {
      return 0;
    }
    std::cout << error.what() << std::endl;
  }
  return 1;
}
