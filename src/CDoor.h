//
// Created by machavi on 5/29/21.
//
#pragma once
#include <string>

#include "CCoordinates.h"

class CDoor {
 public:
  CDoor(int x, int y, int destRoom) : m_Coordinates(x, y), m_DestRoom(destRoom){};
  CDoor(CCordinates coor, int destRoom) : m_Coordinates(coor), m_DestRoom(destRoom){};
  const CCordinates& GetCoordinates() const;
  int GetDestRoom() const;

 private:
  CCordinates m_Coordinates;
  int m_DestRoom;
};

int CDoor::GetDestRoom() const { return m_DestRoom; }
const CCordinates& CDoor::GetCoordinates() const { return m_Coordinates; }