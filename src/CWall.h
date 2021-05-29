//
// Created by machavi on 5/26/21.
//
#pragma once
#include <cmath>

#include "CCoordinates.h"

enum direction { vertical, horizontal };

class CWall {
 public:
  CWall(int x1, int y1, int x2, int y2) : m_Start(x1, y1), m_End(x2, y2) {
    if (m_Start.X() == m_End.X()) {
      m_Direction = vertical;
    } else {
      m_Direction = horizontal;
    }
  };

  const CCordinates& getStart() const;
  const CCordinates& getEnd() const;

  /**
   * checks whether two walls connect on their ends
   * @param other wall to check wit this wall
   * @return true if they connects else false
   */
  bool Connects(const CWall& other) const;
  bool Contains(int X, int Y) const;

 private:
  CCordinates m_Start;
  CCordinates m_End;

  direction m_Direction;
};

const CCordinates& CWall::getStart() const { return m_Start; }
const CCordinates& CWall::getEnd() const { return m_End; }

bool CWall::Connects(const CWall& other) const {
  return (m_Start.X() == other.m_End.X() && m_Start.Y() == other.m_End.Y()) ||
         (m_End.X() == other.m_Start.X() && m_End.Y() == other.m_Start.Y());
}

bool CWall::Contains(int X, int Y) const {
  // todo: napsat to hezci funkci, tyhle ify nejsou hezke
  if (m_Direction == vertical) {
    // check if it lies on the same X coordinate
    if (X == m_Start.X()) {
      // check if Y is between the lies between end and start
      if ((Y >= m_Start.Y() && Y <= m_End.Y()) || (Y >= m_End.Y() && Y <= m_Start.Y())) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    // check if it lies on the same Y coordinate
    if (Y == m_End.Y()) {
      // check if X is between the lies between end and start
      if ((X >= m_Start.X() && X <= m_End.X()) || (X >= m_End.X() && X <= m_Start.X())) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }
}