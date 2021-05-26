//
// Created by machavi on 5/26/21.
//
#pragma once
#include <vector>

class CWall {
 public:
  CWall(int x1, int y1, int x2, int y2) : m_X1(x1), m_Y1(y1), m_X2(x2), m_Y2(y2){};
  std::pair<int, int> getStart();
  std::pair<int, int> getEnd();

  /**
   * checks whether two walls connect on their ends
   * @param other wall to check wit this wall
   * @return true if they connects else false
   */
  bool Connects(const CWall& other);

 private:
  int m_X1;
  int m_Y1;
  int m_X2;
  int m_Y2;
};

std::pair<int, int> CWall::getStart() { return std::make_pair(m_X1, m_Y1); }
std::pair<int, int> CWall::getEnd() { return std::make_pair(m_X2, m_Y2); }

bool CWall::Connects(const CWall& other) {
  return (m_X1 == other.m_X2 && m_Y1 == other.m_Y2) || (m_X2 == other.m_X1 && m_Y2 == other.m_Y1);
}