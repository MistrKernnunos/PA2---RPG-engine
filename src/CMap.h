//
// Created by machavi on 5/7/21.
//

#pragma once
#include <memory>
#include <ostream>
#include <vector>

#include "CEntityLoader.h"
#include "CFileLoaderIterator.h"
#include "CWall.h"
#include "EMapElem.h"
class CGame;
class CMap {
 public:
  CMap(int ID, const std::string& name, CGame& game);
  ~CMap() = default;
  /**
   * loads map from xml tree
   * @param iterator iterator over xml tree pointing to head of room
   * @return true if succeeded or false
   */
  bool Load(CFileLoaderIt iterator, std::weak_ptr<CMap> roomPtr);

  /**
   * saves map to file
   * @param it where to save it
   * @return true if successful
   */
  bool Save(CFileLoaderIt it) const;

  /**
   * executes turns for all entites in room
   */
  bool ExecuteTurns();
  /**
   * transfers entity to this room
   * @param entity which entity to this room
   * @param doorNumber number of door to which entity arrives
   * @return true if succeeded, else if not
   */
  bool TransferEntityToRoom(std::shared_ptr<CEntity> entity, const CCoordinates& spawnpoint);

  friend std::ostream& operator<<(std::ostream& os, const CMap& room);
  /**
   *tries to move the entity from start to end in range
   * @param start of the move
   * @param end of the move
   * @param range the max range
   * @return true if possible, false if not
   */
  bool Move(const CCoordinates& start, const CCoordinates& end, int range);

  /**
   * renders the map
   */
  void Render();

  /**
   * finds entities in range around pos
   * @param pos position from where to look
   * @param range in which to look
   * @return vector of found entities
   */
  std::vector<std::shared_ptr<CEntity>> EntitiesInRange(const CCoordinates& pos, int range) const;
  /**
   * find lootable entities in loot range
   * @param pos position from to loot
   * @return vector of lootable entities
   */
  std::vector<std::shared_ptr<CEntity>> GetLootableEntities(const CCoordinates& pos) const;

  /**
   * gets what is on position
   * @param pos position to check
   * @return EMapElem
   */
  EMapElem isAtPosition(const CCoordinates& pos) const;

 private:
  // map of the room
  std::vector<std::vector<EMapElem>> m_Map;
  // entities present in the room and their coordinates
  std::map<CCoordinates, std::shared_ptr<CEntity>> m_Entities;
  std::vector<std::shared_ptr<CEntity>> m_EntitiesVector;
  // vector of walls, they are defined by two pairs of coordinates
  std::vector<std::unique_ptr<CWall>> perimeterWalls;
  std::vector<std::unique_ptr<CWall>> innerWalls;
  int m_ID;
  std::string m_Name;
  CGame& m_Game;
  int m_Heigth = 0;
  int m_Width = 0;

  /**
   * loads perimeter walls to the room from xml tree
   * @param iterator  pointing to perimeter node
   * @return true if successfully loaded
   */
  bool loadPerimeter(CFileLoaderIt iterator);
  /**
   * loads inner walls from xml tree
   * @param iterator  pointing to inner node
   * @return true if successfully loaded
   */
  bool loadInner(CFileLoaderIt iterator);
  /**
   * checks perimeter walls if they create single shape
   * @return returns true if the the walls create single shape
   */
  bool checkPerimeter();

  bool saveWalls(CFileLoaderIt it, const std::vector<std::unique_ptr<CWall>>& walls) const;

  bool saveEntities(CFileLoaderIt it) const;

  void exportToMap();
};