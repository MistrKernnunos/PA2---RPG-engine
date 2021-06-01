//
// Created by machavi on 5/29/21.
//
#pragma once
#include <iostream>

#include "CFileLoaderIterator.h"

class CCordinates {
 public:
  CCordinates() = default;
  CCordinates(int x, int y) : m_X(x), m_Y(y){};
  CCordinates(const CCordinates& other) : m_X(other.m_X), m_Y(other.m_Y){};
  CCordinates& operator=(const CCordinates& other) = default;

  int X() const;
  int Y() const;
  bool Load(CFileLoaderIt iterator);
  static CCordinates LoadCoordinates(CFileLoaderIt iterator);
  friend std::ostream& operator<<(std::ostream& os, const CCordinates& cordinates);

 private:
  int m_X = 0;
  int m_Y = 0;
};

int CCordinates::X() const { return m_X; }
int CCordinates::Y() const { return m_Y; }

bool CCordinates::Load(CFileLoaderIt iterator) {
  iterator.Child();//move to X node
  iterator.Next();

  if (!(iterator.GetName() == "X")) {
    throw std::invalid_argument("bad coordinates node name");
    return false;
  }
  m_X = std::stoi(iterator.GetContent());
  iterator.Next();
  iterator.Next();

  if (!(iterator.GetName() == "Y")) {
    throw std::invalid_argument("bad coordinates node name");
    return false;
  }
  m_Y = std::stoi(iterator.GetContent());
  return true;
}

CCordinates CCordinates::LoadCoordinates(CFileLoaderIt iterator) {
  CCordinates coordinates;
  coordinates.Load(iterator);
  return coordinates;
}
std::ostream& operator<<(std::ostream& os, const CCordinates& cordinates) {
  os << "m_X: " << cordinates.m_X << " m_Y: " << cordinates.m_Y;
  return os;
}
