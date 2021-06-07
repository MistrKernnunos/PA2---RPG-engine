//
// Created by machavi on 6/3/21.
//
#include "CInterface.h"

class CInterfaceLocator {
 public:
  static CInterface& getInterface();
  static void provide(CInterface* interface);

 private:
  static CInterface* m_Interface;
};
