#include <iostream>

#include "CInterface.h"
#include "CInterfaceLocator.h"
#include "CMenu.h"
int main() {
  CInterface interface(std::cout, std::cin);
  CInterfaceLocator::provide(&interface);
  CGame game(interface);
  CMenu menu(interface);
  menu.RunMenu(game);
  game.Start();

  //  CFileLoader loader;
  //  loader.loadXmlFile("./map.xml");
  //  CFileLoaderIt res = loader.GetNode("room");
  //  CRoom room;
  //  try {
  //    room.Load(res);
  //  } catch (std::exception& error) {
  //    std::cout << error.what() << std::endl;
  //  }

  return 1;
}
