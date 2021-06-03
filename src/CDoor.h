//
// Created by machavi on 5/29/21.
//
#pragma once
#include <string>
#include <vector>

#include "CCoordinates.h"
#include "CFileLoaderIterator.h"

class CDoor {
 public:
  CDoor() = default;
  CDoor(int x, int y, int destRoom) : m_Coordinates(x, y), m_DestRoom(destRoom){};
  CDoor(CCoordinates coor, int destRoom) : m_Coordinates(coor), m_DestRoom(destRoom){};
  CDoor(const CDoor& other) : m_Coordinates(other.m_Coordinates), m_DestRoom(other.m_DestRoom){};
  const CCoordinates& GetCoordinates() const;
  int GetDestRoom() const;

  bool Load(CFileLoaderIt iterator);
  static CDoor LoadDoor(CFileLoaderIt iterator);

  void PrintToBuffer(std::vector<std::vector<std::string>>& outputBuffer);

 private:
  CCoordinates m_Coordinates;
  int m_DestRoom = 0;
  const static std::string m_Apperance;
};
