//
// Created by machavi on 6/1/21.
//
#pragma once
#include <map>
#include <string>

#include "CControler.h"
#include "CCoordinates.h"
#include "CEntity.h"
#include "CFactory.h"
#include "CFileLoaderIterator.h"
#include "CPlayer.h"
#include "CPlayerController.h"
#include "CZombie.h"
#include "CZombieController.h"
class CEntityLoader {
 public:
  CEntityLoader();
  std::map<CCoordinates, std::shared_ptr<CEntity>> LoadEntities(CFileLoaderIt iterator);

 private:
  CFactory<CEntity, std::string> m_EntityFactory;
  CFactory<CControler, std::string> m_ControlerFactory;
};
