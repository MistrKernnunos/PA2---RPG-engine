//
// Created by machavi on 5/7/21.
//

#pragma once
#include <memory>
#include <ostream>
#include <vector>

//#include "CEntity.h"
#include "CFileLoaderIterator.h"
//#include "CGame.h"
//#include "CInterface.h"
#include "CDoor.h"
#include "CEntityLoader.h"
#include "CWall.h"
#include "EMapElem.h"

class CRoom {
 public:
  CRoom() = default;
  /**
   * loads room from xml tree
   * @param iterator iterator over xml tree pointing to head of room
   * @return true if succeeded or false
   */
  bool Load(CFileLoaderIt iterator);

  //  bool Save(std::string filename) const;

  /**
   * executes turns for all entites in room
   */
  //  void ExecuteTurns(CGame& game);
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
  //  void Print(const CInterface& interface);

  //  bool MoveEntity();

  friend std::ostream& operator<<(std::ostream& os, const CRoom& room);

 private:
  // map of the room
  std::vector<std::vector<EMapElem>> m_Map;
  // entities present in the room and their coordinates
  std::vector<std::shared_ptr<CEntity>> m_Entities;
  // index is door which this connection belong to,
  // pointer to room which connect and door number
  std::vector<std::unique_ptr<CDoor>> m_Doors;
  // vector of walls, they are defined by two pairs of coordinates
  std::vector<std::unique_ptr<CWall>> perimeterWalls;
  std::vector<std::unique_ptr<CWall>> innerWalls;
  int m_ID;
  std::string m_Name;

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
};

bool CRoom::Load(CFileLoaderIt iterator) {
  if (iterator.GetName() != "room") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  auto prop = iterator.GetProperties();  // get properties of room (name and ID)
  if (prop.empty()) {
    throw std::invalid_argument("no property in room node");
    return false;
  }
  if (prop.front().first == "ID") {
    m_ID = std::stoi(prop.front().second);
  }
  prop.pop_front();
  if (prop.front().first == "name") {
    m_Name = prop.front().first;
  }
  if (m_Name.empty() || m_ID == 0) {  // check if they were valid
    throw std::invalid_argument("invalid room properties");
    return false;
  }
  if (!iterator.Child()) return false;         // move to text node
  if (!iterator.Next()) return false;          // move to perimeter node
  if (!loadPerimeter(iterator)) return false;  // load perimeter walls
  if (!checkPerimeter()) return false;         // checks whether perimeter walls create continuous shape
  if (!iterator.Next()) return false;          // move to text node
  if (!iterator.Next()) return false;          // move to perimeter node
  if (!loadInner(iterator)) return false;      // load inner walls
  if (!iterator.Next()) return false;          // move to text node
  if (!iterator.Next()) return false;          // move to doors node
  if (!loadDoors(iterator)) return false;      // load doors
  CEntityLoader entityLoader;
  if (!iterator.Next()) return false;  // move to text node
  if (!iterator.Next()) return false;  // move to doors node
  m_Entities = entityLoader.LoadEntities(iterator);
  return true;
}

bool CRoom::loadPerimeter(CFileLoaderIt iterator) {
  if (iterator.GetName() != "perimeter") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
#ifdef DEBUG
  std::cout << "perimeter" << std::endl;
#endif
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    perimeterWalls.push_back(std::make_unique<CWall>(CWall::LoadWall(iterator)));
  }
  return true;
}
bool CRoom::loadInner(CFileLoaderIt iterator) {
  if (iterator.GetName() != "inner") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
#ifdef DEBUG
  std::cout << "inner" << std::endl;
#endif
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    innerWalls.push_back(std::make_unique<CWall>(CWall::LoadWall(iterator)));
  }
  return true;
}

bool CRoom::checkPerimeter() {
  if (!perimeterWalls.front()->Connects(*perimeterWalls.back())) {
    return false;
  }
  size_t numOfWalls = perimeterWalls.size() - 1;
  for (size_t i = 0; i < numOfWalls; ++i) {
    if (!perimeterWalls.at(i)->Connects(*perimeterWalls.at(i + 1))) {
      throw std::invalid_argument("perimeter walls do not create continuous shape");
      return false;
    }
  }
  return true;
}

bool CRoom::loadDoors(CFileLoaderIt iterator) {
  if (iterator.GetName() != "doors") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  // move to door node
  iterator.Child();
  iterator.Next();
  // load doors
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    m_Doors.push_back(std::make_unique<CDoor>(CDoor::LoadDoor(iterator)));
  }
  return true;
}
std::ostream& operator<<(std::ostream& os, const CRoom& room) {
  std::vector<std::vector<std::string>> outputBuffer;

  for (auto& elem : room.perimeterWalls) {
    elem->Print(outputBuffer, "\33[47m \33[0m");
  }

  for (auto& elem : room.innerWalls) {
    elem->Print(outputBuffer, "\33[47m \33[0m");
  }
  for (auto& elem : outputBuffer) {
    for (auto& elemInner : elem) {
      os << elemInner;
    }
    os << std::endl;
  }
  return os;
}
