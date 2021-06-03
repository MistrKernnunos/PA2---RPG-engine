//
// Created by machavi on 6/1/21.
//
#include "CEntityLoader.h"
CEntityLoader::CEntityLoader() {
  m_ControlerFactory.Register("zombie", CZombieController::Create);
  m_EntityFactory.Register("zombie", CZombie::Create);
  m_ControlerFactory.Register("player", CPlayerController::Create);
  m_EntityFactory.Register("player", CPlayer::Create);
}

std::map<CCoordinates, std::shared_ptr<CEntity>> CEntityLoader::LoadEntities(CFileLoaderIt iterator) {
  std::map<CCoordinates, std::shared_ptr<CEntity>> entities;
  if (iterator.GetName() != "entities") {
    throw std::invalid_argument("wrong entity node");
    return entities;
  }

  iterator.Child();  // go to entity node
  iterator.Next();
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    auto prop = iterator.GetProperties();
    if (prop.empty() || prop.size() != 1 || prop.front().first != "entityID") {
      throw std::invalid_argument("wrong entity node ");
      return entities;
    }
    auto entity = m_EntityFactory.createObject(prop.front().second);
    if (!entity) {
      return entities;
    }
    entity->Load(iterator);
    entity->AttachController(m_ControlerFactory.createObject(prop.front().second));
    entities.insert(std::make_pair(entity->GetCoordinates(), entity));
  }
  return entities;
}
