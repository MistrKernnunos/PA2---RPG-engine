//
// Created by machavi on 5/29/21.
//
#pragma once
#include <string>

#include "CCoordinates.h"
#include "CFileLoaderIterator.h"

class CDoor {
 public:
  CDoor() = default;
  CDoor(int x, int y, int destRoom) : m_Coordinates(x, y), m_DestRoom(destRoom){};
  CDoor(CCordinates coor, int destRoom) : m_Coordinates(coor), m_DestRoom(destRoom){};
  CDoor(const CDoor& other) : m_Coordinates(other.m_Coordinates), m_DestRoom(other.m_DestRoom){};
  const CCordinates& GetCoordinates() const;
  int GetDestRoom() const;

  bool Load(CFileLoaderIt iterator);
  static CDoor LoadDoor(CFileLoaderIt iterator);

 private:
  CCordinates m_Coordinates;
  int m_DestRoom = 0;
};

int CDoor::GetDestRoom() const { return m_DestRoom; }
const CCordinates& CDoor::GetCoordinates() const { return m_Coordinates; }

CDoor CDoor::LoadDoor(CFileLoaderIt iterator) {
  CDoor door;
  door.Load(iterator);
  return door;
}

bool CDoor::Load(CFileLoaderIt iterator) {
  if (iterator.GetName() != "door") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  auto prop = iterator.GetProperties();
  if (prop.front().first != "IDroom") {
    throw std::invalid_argument("wrong properties");
    return false;
  }
  m_DestRoom = std::stoi(prop.front().second);
  iterator.Child();  // move to  coordinate
  iterator.Next();
  m_Coordinates = CCordinates::LoadCoordinates(iterator);
#ifdef DEBUG
  std::cout << m_Coordinates << std::endl;
#endif
  return true;
}