
#pragma once
#include "CGame.h"

class CAplication {
 public:
  CAplication(CInterface interface);

  CAplication & Run();

 private:
  CGame m_Game;
};
