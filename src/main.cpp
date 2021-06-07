#include <iostream>

#include "CFileLoader.h"
#include "CFileLoaderIterator.h"
#include "CInterface.h"
#include "CInterfaceLocator.h"
#include "CMenu.h"
int main() {
  CInterface interface(std::cout, std::cin);
  CInterfaceLocator::provide(&interface);
  CGame game(interface);
  CMenu menu(interface);
  menu.RunMenu(game);
  //  game.Start();
  game.Save();

  //  std::list<std::pair<std::string, std::string>> propList;
  //  propList.push_back(std::make_pair("ID", "666"));
  //  CFileLoader loader;
  //  CFileLoaderIt it = loader.NewDoc("map");
  //  it.CreateNewTextChildNode("testNodeName", "snad to bude fungovat");
  //  it.AddProperties(propList);
  //  loader.SaveFile("./test.xml");

  //  CFileLoader loader;
  //  loader.LoadXmlFile("./map.xml");
  //  CFileLoaderIt res = loader.GetNode("room");
  //  CRoom room;
  //  try {
  //    room.Load(res);
  //  } catch (std::exception& error) {
  //    std::cout << error.what() << std::endl;
  //  }

  return 1;
}
