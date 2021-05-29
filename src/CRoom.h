//
// Created by machavi on 5/7/21.
//

#pragma once
#include <memory>
#include <vector>

//#include "CEntity.h"
#include "CFileLoaderIterator.h"
//#include "CGame.h"
//#include "CInterface.h"
#include "CDoor.h"
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

 private:
  // map of the room
  std::vector<std::vector<EMapElem>> m_Map;
  // entities present in the room and their coordinates
  //  std::vector<std::tuple<std::unique_ptr<CEntity>, int, int>> m_Entities;
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
   * loads single wall from xml tree
   * throws exception if coordinate is not valid or the wall is not straight
   * @param iterator pointing to wall node
   * @return wall which it loaded
   */
  CWall loadWall(CFileLoaderIt iterator);
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
  auto prop = iterator.GetProperties();  // get properties of room (name and ID)
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
  return true;
}

bool CRoom::loadPerimeter(CFileLoaderIt iterator) {
  if (iterator.GetName() != "perimeter") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    perimeterWalls.push_back(std::make_unique<CWall>(loadWall(iterator)));
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
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    perimeterWalls.push_back(std::make_unique<CWall>(loadWall(iterator)));
  }
  return true;
}

CWall CRoom::loadWall(CFileLoaderIt iterator) {
  if (iterator.GetName() != "wall") {
    throw std::invalid_argument("wrong node");
  }
  iterator.Child();
  iterator.Next();
  int coordinates[4];
  for (size_t i = 0; i < 4; ++i, iterator.Next(), iterator.Next()) {
    coordinates[i] = std::stoi(iterator.GetContent());
  }
  if (coordinates[0] != coordinates[2] && coordinates[1] != coordinates[3]) {
    throw std::invalid_argument("wall is not straight");
  }
#ifdef DEBUG
  for (int elem : coordinates) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
#endif
  return CWall(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
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
    auto prop = iterator.GetProperties();
    int destRoom = 0;
    if (prop.front().first == "IDroom") {
      destRoom = std::stoi(prop.front().second);
    }
    iterator.Child();  // move to first coordinate
    iterator.Next();
    CCordinates coor;
    if (!coor.Load(iterator)) return false;
    iterator.Parent();  // return to door level
#ifdef DEBUG
    std::cout << coor.X() << " " << coor.Y() << std::endl;
#endif
    m_Doors.push_back(std::make_unique<CDoor>(coor, destRoom));
  }
  return true;
}
