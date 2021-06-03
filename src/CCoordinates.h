//
// Created by machavi on 5/29/21.
//
#pragma once
#include <iostream>

#include "CFileLoaderIterator.h"

class CCoordinates {
 public:
  CCoordinates() = default;
  CCoordinates(int x, int y) : m_X(x), m_Y(y){};
  CCoordinates(const CCoordinates& other) : m_X(other.m_X), m_Y(other.m_Y){};
  CCoordinates& operator=(const CCoordinates& other) = default;

  int X() const;
  int Y() const;
  bool Load(CFileLoaderIt iterator);
  static CCoordinates LoadCoordinates(CFileLoaderIt iterator);
  friend std::ostream& operator<<(std::ostream& os, const CCoordinates& cordinates);
  bool operator==(const CCoordinates& rhs) const;
  bool operator!=(const CCoordinates& rhs) const;
  bool operator<(const CCoordinates& rhs) const;
  bool operator>(const CCoordinates& rhs) const;
  bool operator<=(const CCoordinates& rhs) const;
  bool operator>=(const CCoordinates& rhs) const;
  int Distance(const CCoordinates& other);

 private:
  int m_X = 0;
  int m_Y = 0;
};
