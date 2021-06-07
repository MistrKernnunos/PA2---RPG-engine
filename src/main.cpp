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
  CMenu menu(interface);
  if (menu.RunMenu(game)) {
    if (game.IsInitialized()) {
      game.Start();
    }
  }
  return 1;
}
