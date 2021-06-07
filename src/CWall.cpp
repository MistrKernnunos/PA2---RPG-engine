//
// Created by machavi on 5/26/21.
//
#include "CWall.h"
const std::string CWall::m_Apperance = "\33[1;44m#\33[0m";

const CCoordinates& CWall::getStart() const { return m_Start; }
const CCoordinates& CWall::getEnd() const { return m_End; }

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

CWall CWall::LoadWall(CFileLoaderIt it) {
  CWall wall;
  wall.Load(it);
  return wall;
}

bool CWall::Load(CFileLoaderIt iterator) {
  if (iterator.GetName() != "wall") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  iterator.Child();  // move to coordinates node
  iterator.Next();
  //----------load start coordinates-----
  auto prop = iterator.GetProperties();
  if (prop.front().first != "name" || prop.front().second != "start") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  m_Start = CCoordinates::LoadCoordinates(iterator);
  prop.erase(prop.begin(), prop.end());
  iterator.Next();  // move to next coordinates
  iterator.Next();

  //----------load end coordinates-----
  prop = iterator.GetProperties();
  if (prop.front().first != "name" || prop.front().second != "end") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  m_End = CCoordinates::LoadCoordinates(iterator);

  //-----validate wall----
  if (m_Start.X() != m_End.X() && m_Start.Y() != m_End.Y()) {
    throw std::invalid_argument("wall is not straight");
    return false;
  }
  //---asses direction----
  if (m_Start.X() == m_End.X()) {
    m_Direction = vertical;
  } else {
    m_Direction = horizontal;
  }
#ifdef DEBUG
  std::cout << "start of wall: " << m_Start << std::endl;
  std::cout << "end of wall: " << m_End << std::endl;
#endif
  return true;
}
void CWall::PrintToBuffer(std::vector<std::vector<std::string>>& outputBuffer, const std::string& floor) {
  size_t len = 0;
  if (m_Direction == vertical) {
    len = std::abs(m_Start.Y() - m_End.Y()) + 1;
  } else {
    len = std::abs(m_Start.X() - m_End.X()) + 1;
  }
  size_t maxHeight = std::max(m_Start.Y(), m_End.Y());
  size_t maxWidth = std::max(m_Start.X(), m_End.X());

  if (outputBuffer.size() < maxHeight) {
    outputBuffer.resize(maxHeight + 1);
  }
  for (auto& elem : outputBuffer) {
    if (elem.size() < maxWidth) {
      elem.resize(maxWidth + 1, floor);
    }
  }
  for (size_t i = 0; i < len; ++i) {
    size_t x = 0;
    size_t y = 0;
    if (m_Direction == vertical) {
      x = m_Start.X();
      y = std::min(m_Start.Y(), m_End.Y()) + i;
    } else {
      y = m_Start.Y();
      x = std::min(m_Start.X(), m_End.X()) + i;
    }
    outputBuffer.at(y).at(x) = m_Apperance;
  }
}
void CWall::ExportToMap(std::vector<std::vector<EMapElem>>& map) {
  size_t len = 0;
  if (m_Direction == vertical) {
    len = std::abs(m_Start.Y() - m_End.Y()) + 1;
  } else {
    len = std::abs(m_Start.X() - m_End.X()) + 1;
  }
  size_t maxHeight = std::max(m_Start.Y(), m_End.Y());
  size_t maxWidth = std::max(m_Start.X(), m_End.X());

  if (map.size() < maxHeight) {
    map.resize(maxHeight + 1);
  }
  for (auto& elem : map) {
    if (elem.size() < maxWidth) {
      elem.resize(maxWidth + 1, EMapElem::FLOOR);
    }
  }

  for (size_t i = 0; i < len; ++i) {
    size_t x = 0;
    size_t y = 0;
    if (m_Direction == vertical) {
      x = m_Start.X();
      y = std::min(m_Start.Y(), m_End.Y()) + i;
    } else {
      y = m_Start.Y();
      x = std::min(m_Start.X(), m_End.X()) + i;
    }
    map.at(y).at(x) = EMapElem::WALL;
  }
}
bool CWall::Save(CFileLoaderIt it) {
  if (it.GetName() != "wall") {
    return false;
  }
  std::list<std::pair<std::string, std::string>> propList;
  propList.emplace_back("name", "start");
  it.CreateNewChildNode("coordinates");
  it.CreateNewChildNode("coordinates");
  it.Child();
  it.AddProperties(propList);
  m_Start.Save(it);

  it.Next();
  propList.clear();
  propList.emplace_back("name", "end");
  it.AddProperties(propList);
  return m_End.Save(it);
}
