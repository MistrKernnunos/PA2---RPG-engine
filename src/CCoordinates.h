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

  /**
   * access X coordinate
   * @return Y coordinate
   */
  int X() const;
  /**
   * access Y coordinate
   * @return Y coordinate
   */
  int Y() const;
  /**
   * loads coordinates to this coordinate
   * @param iterator from where to load
   * @return true if successful
   */
  bool Load(CFileLoaderIt iterator);
  /**
   * saves coordinates to file
   * @param it it to node
   * @return true if successful
   */
  bool Save(CFileLoaderIt it) const;

  /**
   * static function to create and load coordinates
   * @param iterator iterator to coordinate node
   * @return created Coordinates
   */
  static CCoordinates LoadCoordinates(CFileLoaderIt iterator);

  friend std::ostream& operator<<(std::ostream& os, const CCoordinates& cordinates);

  bool operator==(const CCoordinates& rhs) const;
  bool operator!=(const CCoordinates& rhs) const;
  bool operator<(const CCoordinates& rhs) const;
  bool operator>(const CCoordinates& rhs) const;
  bool operator<=(const CCoordinates& rhs) const;
  bool operator>=(const CCoordinates& rhs) const;

 private:
  int m_X = 0;
  int m_Y = 0;
};
