//
// Created by machavi on 5/7/21.
//

#include "CRoom.h"

#include <queue>
#include <set>

#include "CGame.h"
bool CRoom::Load(CFileLoaderIt iterator, std::weak_ptr<CRoom> roomPtr) {
  if (iterator.GetName() != "room") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  auto prop = iterator.GetProperties();  // get properties of room (name and ID)
  if (prop.empty()) {
    throw std::invalid_argument("no property in room node");
    return false;
  }
  if (prop.front().first == "ID") {
    m_ID = std::stoi(prop.front().second);
  }
  prop.pop_front();
  if (prop.front().first == "name") {
    m_Name = prop.front().first;
  }
  if (m_Name.empty() || m_ID == 0) {  // check if they were valid
    throw std::invalid_argument("invalid room properties");
    return false;
  }
  if (!iterator.Child()) return false;         // move to text node
  if (!iterator.Next()) return false;          // move to perimeter node
  if (!loadPerimeter(iterator)) return false;  // load perimeter walls
  if (!checkPerimeter()) return false;         // checks whether perimeter walls create continuous shape
  if (!iterator.Next()) return false;          // move to text node
  if (!iterator.Next()) return false;          // move to perimeter node
  if (!loadInner(iterator)) return false;      // load inner walls
  if (!iterator.Next()) return false;          // move to text node
  if (!iterator.Next()) return false;          // move to doors node
  if (!loadDoors(iterator)) return false;      // load doors
  CEntityLoader entityLoader;                  // init entity loader
  if (!iterator.Next()) return false;          // move to text node
  if (!iterator.Next()) return false;          // move to doors node
  m_Entities = entityLoader.LoadEntities(iterator);
  for (auto& elem : m_Entities) {
    elem.second->InsertIntoRoom(roomPtr);
  }
  exportToMap();
  return true;
}

bool CRoom::loadPerimeter(CFileLoaderIt iterator) {
  if (iterator.GetName() != "perimeter") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
#ifdef DEBUG
  std::cout << "perimeter" << std::endl;
#endif
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    perimeterWalls.push_back(std::make_unique<CWall>(CWall::LoadWall(iterator)));
  }
  return true;
}
bool CRoom::loadInner(CFileLoaderIt iterator) {
  if (iterator.GetName() != "inner") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
#ifdef DEBUG
  std::cout << "inner" << std::endl;
#endif
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    innerWalls.push_back(std::make_unique<CWall>(CWall::LoadWall(iterator)));
  }
  return true;
}

bool CRoom::checkPerimeter() {
  if (!perimeterWalls.front()->Connects(*perimeterWalls.back())) {
    return false;
  }
  size_t numOfWalls = perimeterWalls.size() - 1;
  for (size_t i = 0; i < numOfWalls; ++i) {
    if (!perimeterWalls.at(i)->Connects(*perimeterWalls.at(i + 1))) {
      throw std::invalid_argument("perimeter walls do not create continuous shape");
      return false;
    }
  }
  return true;
}

bool CRoom::loadDoors(CFileLoaderIt iterator) {
  if (iterator.GetName() != "doors") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  // move to door node
  iterator.Child();
  iterator.Next();
  // load doors
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    m_Doors.push_back(std::make_unique<CDoor>(CDoor::LoadDoor(iterator)));
  }
  return true;
}
std::ostream& operator<<(std::ostream& os, const CRoom& room) {
  std::vector<std::vector<std::string>> outputBuffer;
  std::string floor = "\33[47m \33[0m";

  //----print walls and doors to buffer----
  for (auto& elem : room.perimeterWalls) {
    elem->PrintToBuffer(outputBuffer, floor);
  }
  for (auto& elem : room.innerWalls) {
    elem->PrintToBuffer(outputBuffer, floor);
  }
  for (auto& elem : room.m_Doors) {
    elem->PrintToBuffer(outputBuffer);
  }
  //----print entities to buffer---
  for (auto& elem : room.m_Entities) {
    elem.second->PrintToBuffer(outputBuffer);
  }
  //----print buffer to stream---
  for (auto& elem : outputBuffer) {
    for (auto& elemInner : elem) {
      os << elemInner;
    }
    os << std::endl;
  }
  return os;
}
bool CRoom::Move(const CCoordinates& start, const CCoordinates& end, int range) {
  // todo BFS na pocitani vzalenosti a jestli se tam lze dostat
  int x = end.X();
  int y = end.Y();
  if (x >= m_Width || x < 0 || y >= m_Heigth || y < 0 || m_Map.at(y).at(x) == EMapElem::ENTITY) {
    return false;
  }

  std::queue<std::pair<CCoordinates, size_t>> toVisit;
  std::set<CCoordinates> visited;
  toVisit.push(std::make_pair(start, 0));
  visited.insert(start);

  while (toVisit.size() > 0) {
    CCoordinates coor = toVisit.front().first;
    int dist = toVisit.front().second;
    toVisit.pop();

    if (coor == end) {
      m_Map.at(start.Y()).at(start.X()) = EMapElem::FLOOR;
      m_Map.at(end.Y()).at(end.X()) = EMapElem::ENTITY;
      auto entity = m_Entities.at(start);
      m_Entities.erase(start);
      m_Entities.insert(std::make_pair(end, entity));
      return true;
    }

    if (dist < range) {
      CCoordinates adjacent[4];
      adjacent[0] = CCoordinates(coor.X() + 1, coor.Y());
      adjacent[1] = CCoordinates(coor.X(), coor.Y() + 1);
      adjacent[2] = CCoordinates(coor.X() - 1, coor.Y());
      adjacent[3] = CCoordinates(coor.X(), coor.Y() - 1);

      for (auto& i : adjacent) {
        if (visited.count(i) == 0) {
          if (i.X() < m_Width && i.X() >= 0 && i.Y() < m_Heigth && i.Y() >= 0 &&
              m_Map.at(i.Y()).at(i.X()) != EMapElem::WALL) {
            toVisit.push(std::make_pair(i, dist + 1));
            visited.insert(i);
          }
        }
      }
    }
  }
  return false;
}

void CRoom::ExecuteTurns() {
  for (auto& elem : m_Entities) elem.second->Turn();
}
void CRoom::Render() { m_Game.Render(); }

CRoom::CRoom(int ID, const std::string& name, CGame& game) : m_ID(ID), m_Name(name), m_Game(game) {}

void CRoom::exportToMap() {
  //----export walls to map---
  for (auto& elem : perimeterWalls) {
    elem->ExportToMap(m_Map);
  }
  for (auto& elem : innerWalls) {
    elem->ExportToMap(m_Map);
  }
  m_Heigth = m_Map.size();
  if (m_Heigth > 0) {
    m_Width = m_Map.front().size();
  } else {
    m_Width = 0;
  }

  //---export entities to map---
  for (auto& elem : m_Entities) {
    CCoordinates coordinate = elem.second->GetCoordinates();
    m_Map.at(coordinate.Y()).at(coordinate.X()) = EMapElem::ENTITY;
  }
}
std::vector<std::shared_ptr<CEntity>> CRoom::PossibleToAttack(const CCoordinates& pos, int range) const {
  std::vector<std::shared_ptr<CEntity>> res;
  std::vector<CCoordinates> resCoordinates;
  // CCordinates and range from start pos
  std::queue<std::pair<CCoordinates, size_t>> toVisit;
  std::set<CCoordinates> visited;
  toVisit.push(std::make_pair(pos, 0));
  visited.insert(pos);

  while (toVisit.size() > 0) {
    CCoordinates coor = toVisit.front().first;
    int dist = toVisit.front().second;
    toVisit.pop();

    if (isAtPosition(coor) == EMapElem::ENTITY) {
      resCoordinates.push_back(coor);
    }
    if (dist < range) {
      CCoordinates adjacent[4];
      adjacent[0] = CCoordinates(coor.X() + 1, coor.Y());
      adjacent[1] = CCoordinates(coor.X(), coor.Y() + 1);
      adjacent[2] = CCoordinates(coor.X() - 1, coor.Y());
      adjacent[3] = CCoordinates(coor.X(), coor.Y() - 1);

      for (auto& i : adjacent) {
        if (visited.count(i) == 0) {
          if (i.X() < m_Width && i.X() >= 0 && i.Y() < m_Heigth && i.Y() >= 0 &&
              m_Map.at(i.Y()).at(i.X()) != EMapElem::WALL) {
            toVisit.push(std::make_pair(i, dist + 1));
            visited.insert(i);
          }
        }
      }
    }
  }
  res.reserve(resCoordinates.size());
  for (auto elem : resCoordinates) {
    if (m_Entities.count(elem) == 1) {
      std::shared_ptr<CEntity> entity = m_Entities.at(elem);
      res.push_back(entity);
    }
  }
  return res;
}
EMapElem CRoom::isAtPosition(const CCoordinates& pos) const {
  int x = pos.X();
  int y = pos.Y();

  if (x >= m_Width || x < 0 || y >= m_Heigth || y < 0) {
    return EMapElem::FLOOR;
  };
  return m_Map.at(y).at(x);
}
