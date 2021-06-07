//
// Created by machavi on 5/29/21.
//
#include "CDoor.h"

const  std::string CDoor::m_Apperance = "\33[101;97m|\33[0m";

int CDoor::GetDestRoom() const { return m_DestRoom; }
const CCoordinates& CDoor::GetCoordinates() const { return m_Coordinates; }

CDoor CDoor::LoadDoor(CFileLoaderIt iterator) {
  CDoor door;
  door.Load(iterator);
  return door;
}

bool CDoor::Load(CFileLoaderIt iterator) {
  if (iterator.GetName() != "door") {
    throw std::invalid_argument("wrong node");
  }
  auto prop = iterator.GetProperties();
  if (prop.front().first != "IDroom") {
    throw std::invalid_argument("wrong properties");
  }
  m_DestRoom = std::stoi(prop.front().second);
  iterator.Child();  // move to  coordinate
  iterator.Next();
  m_Coordinates = CCoordinates::LoadCoordinates(iterator);
#ifdef DEBUG
  std::cout << m_Coordinates << std::endl;
#endif
  return true;
}

void CDoor::PrintToBuffer(std::vector<std::vector<std::string>>& outputBuffer) {
  outputBuffer.at(m_Coordinates.Y()).at(m_Coordinates.X()) = m_Apperance;
}