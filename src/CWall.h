//
// Created by machavi on 5/26/21.
//
#pragma once
#include <cmath>
#include <vector>

#include "CCoordinates.h"
#include "CFileLoaderIterator.h"
#include "EMapElem.h"

enum direction { vertical, horizontal };

class CWall {
 public:
  CWall() = default;
  CWall(int x1, int y1, int x2, int y2) : m_Start(x1, y1), m_End(x2, y2) {
    if (m_Start.X() == m_End.X()) {
      m_Direction = vertical;
    } else {
      m_Direction = horizontal;
    }
  };
  CWall(CCoordinates start, CCoordinates end) : m_Start(start), m_End(end) {
    if (m_Start.X() == m_End.X()) {
      m_Direction = vertical;
    } else {
      m_Direction = horizontal;
    }
  };

  const CCoordinates& getStart() const;
  const CCoordinates& getEnd() const;

  /**
   * checks whether two walls connect on their ends
   * @param other wall to check wit this wall
   * @return true if they connects else false
   */
  bool Connects(const CWall& other) const;
  bool Contains(int X, int Y) const;

  static CWall LoadWall(CFileLoaderIt it);
  bool Load(CFileLoaderIt it);

  void PrintToBuffer(std::vector<std::vector<std::string>>& outputBuffer, const std::string& floor);

  void ExportToMap(std::vector<std::vector<EMapElem>>& map);

 private:
  CCoordinates m_Start;
  CCoordinates m_End;
  const static std::string m_Apperance;
  direction m_Direction = vertical;
};
