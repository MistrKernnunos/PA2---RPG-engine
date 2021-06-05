//
// Created by machavi on 5/7/21.
//

#pragma once
#include <memory>
#include <ostream>
#include <vector>

#include "CDoor.h"
#include "CEntityLoader.h"
#include "CFileLoaderIterator.h"
#include "CWall.h"
#include "EMapElem.h"
class CGame;
class CRoom {
 public:
  CRoom(int ID, const std::string& name, CGame& game);
  ~CRoom() = default;
  /**
   * loads room from xml tree
   * @param iterator iterator over xml tree pointing to head of room
   * @return true if succeeded or false
   */
  bool Load(CFileLoaderIt iterator, std::weak_ptr<CRoom> roomPtr);

  //  bool Save(std::string filename) const;

  /**
   * executes turns for all entites in room
   */
  void ExecuteTurns();
  /**
   * transfers entity to this room
   * @param entity which entity to this room
   * @param doorNumber number of door to which entity arrives
   * @return true if succeeded, else if not
   */
  //  bool TransferEntityToRoom(std::shared_ptr<CEntity> entity, int doorNumber);
  /**
   * transfers entity from this room to dest room
   * @param dest room where to transfer the entity
   * @param entity entity which to transfer
   * @param doorNumber which door is used
   * @return true if succeeded, else if not
   */
  //  bool TransferEntityFromRoom(std::shared_ptr<CRoom> dest, std::shared_ptr<CEntity> entity, int doorNumber);
  /**
   * prints room to the interface
   * @param interface interface to print through
   */
  //    void PrintToBuffer(const CInterface& interface);

  //  bool MoveEntity();

  friend std::ostream& operator<<(std::ostream& os, const CRoom& room);

  bool Move(const CCoordinates& start, const CCoordinates& end, int range);

  void Render();

  std::vector<std::shared_ptr<CEntity>> EntitiesInRange(const CCoordinates& pos, int range) const;

  EMapElem isAtPosition(const CCoordinates& pos) const;

 private:
  // map of the room
  std::vector<std::vector<EMapElem>> m_Map;
  // entities present in the room and their coordinates
  std::map<CCoordinates, std::shared_ptr<CEntity>> m_Entities;
  // index is door which this connection belong to,
  // pointer to room which connect and door number
  std::vector<std::unique_ptr<CDoor>> m_Doors;
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
  /**
   * loads doors to this room
   * @param iterator pointing to door section
   * @return true if successful, false if not
   */
  bool loadDoors(CFileLoaderIt iterator);

  void exportToMap();
};