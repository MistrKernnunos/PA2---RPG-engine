//
// Created by machavi on 6/1/21.
//
#pragma once
#include <map>
#include <set>
#include <string>

#include "CControler.h"
#include "CCoordinates.h"
#include "CEntity.h"
#include "CFactory.h"
#include "CFileLoaderIterator.h"
/**
 * facilitates entity loading and creating
 */
class CEntityLoader {
 public:
  CEntityLoader();
  /**
   * creates and loads entity
   * @param iterator iterator to entities node
   * @return map of entities by coordinates
   */
  std::map<CCoordinates, std::shared_ptr<CEntity>> LoadEntities(CFileLoaderIt iterator);
  /**
   * returns empty entity according to its id
   * @param id id of the entity
   * @return entity as shared ptr
   */
  std::shared_ptr<CEntity> CreateEntity(const std::string& id);

 private:
  CFactory<CEntity, std::string> m_EntityFactory;
  CFactory<CControler, std::string> m_ControlerFactory;
  std::set<std::string> m_HasController;
};
