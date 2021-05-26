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
  std::vector<std::pair<std::shared_ptr<CRoom>, int>> m_ConnectedRooms;
  // vector of walls, they are defined by two pairs of coordinates
  std::vector<CWall> perimeterWalls;
  std::vector<CWall> innerWalls;

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
};

bool CRoom::Load(CFileLoaderIt iterator) {
  if (!iterator.Child()) return false;         // move to text node
  if (!iterator.Next()) return false;          // move to perimeter node
  if (!loadPerimeter(iterator)) return false;  // load perimeter walls
  if (!checkPerimeter()) return false;         // checks whether perimeter walls create continuous shape
  if (!iterator.Next()) return false;          // move to text node
  if (!iterator.Next()) return false;          // move to perimeter node
  if (!loadInner(iterator)) return false;      // load inner walls
  return true;
}

bool CRoom::loadPerimeter(CFileLoaderIt iterator) {
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    try {
      perimeterWalls.push_back(loadWall(iterator));
    } catch (std::exception& error) {
      std::cout << error.what() << std::endl;
      return false;
    }
  }
  return true;
}
bool CRoom::loadInner(CFileLoaderIt iterator) {
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    try {
      innerWalls.push_back(loadWall(iterator));
    } catch (std::exception& error) {
      std::cout << error.what() << std::endl;
      return false;
    }
  }
  return true;
}

CWall CRoom::loadWall(CFileLoaderIt iterator) {
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
  if (!perimeterWalls.front().Connects(perimeterWalls.back())) {
    return false;
  }
  size_t numOfWalls = perimeterWalls.size() - 1;
  for (size_t i = 0; i < numOfWalls; ++i) {
    if (!perimeterWalls.at(i).Connects(perimeterWalls.at(i + 1))) {
      throw std::invalid_argument("perimeter walls do not create continuous shape");
      return false;
    }
  }
  return true;
}