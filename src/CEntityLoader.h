//
// Created by machavi on 6/1/21.
//
#include <string>
#include <vector>

#include "CEntity.h"
#include "CFactory.h"
#include "CFileLoaderIterator.h"
#include "CZombie.h"
class CEntityLoader {
 public:
  CEntityLoader();
  std::vector<std::shared_ptr<CEntity>> LoadEntities(CFileLoaderIt iterator);

 private:
  CFactory<CEntity, std::string> m_EntityFactory;
};

CEntityLoader::CEntityLoader() { m_EntityFactory.Register("zombie", CZombie::Create); }

std::vector<std::shared_ptr<CEntity>> CEntityLoader::LoadEntities(CFileLoaderIt iterator) {
  std::vector<std::shared_ptr<CEntity>> entities;
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
    entities.push_back(entity);
  }
  return entities;
}
