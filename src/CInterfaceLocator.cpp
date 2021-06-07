//
// Created by machavi on 6/3/21.
//

#include "CInterfaceLocator.h"
CInterface* CInterfaceLocator::m_Interface = nullptr;

CInterface& CInterfaceLocator::getInterface() { return *CInterfaceLocator::m_Interface; }
void CInterfaceLocator::provide(CInterface* interface) { CInterfaceLocator::m_Interface = interface; }
