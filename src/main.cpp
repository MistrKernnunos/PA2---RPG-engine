#include <iostream>

#include "CFileLoader.h"
#include "CRoom.h"
//#include "CAplication.h"
//#include "CInterface.h"
//#include "CMenu.h"
// int main() {
//  CInterface interface(std::cout, std ::cin);
//  CGame game(interface);
//  CMenu menu(interface);
//  menu.RunMenu(game);
//}
int main() {
  CFileLoader loader;
  loader.loadXmlFile("./map.xml");
  CFileLoaderIt res = loader.GetNode("room");
  CRoom room;
  try {
    room.Load(res);
  } catch (std::exception & error) {
    std::cout << error.what() << std::endl;
  }

  return 1;
}
