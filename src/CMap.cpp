//
// Created by machavi on 5/7/21.
//
#define LOOT_RANGE 5
#include "CMap.h"

#include <queue>
#include <set>

#include "CGame.h"
#include "CInterfaceLocator.h"
bool CMap::Load(CFileLoaderIt iterator, std::weak_ptr<CMap> mapPtr) {
  if (iterator.GetName() != "room") {
    throw std::invalid_argument("wrong node");
  }
  auto prop = iterator.GetProperties();  // get properties of room (name and ID)
  if (prop.empty()) {
    throw std::invalid_argument("no property in room node");
  }
  if (prop.front().first == "ID") {
    m_ID = std::stoi(prop.front().second);
  }
  prop.pop_front();
  if (prop.front().first == "name") {
    m_Name = prop.front().second;
  }
  if (m_Name.empty() || m_ID == 0) {  // check if they were valid
    throw std::invalid_argument("invalid room properties");
  }
  if (!iterator.Child()) return false;         // move to text node
  if (!iterator.Next()) return false;          // move to perimeter node
  if (!loadPerimeter(iterator)) return false;  // load perimeter walls
  if (!checkPerimeter()) return false;         // checks whether perimeter walls create continuous shape
  if (!iterator.Next()) return false;          // move to text node
  if (!iterator.Next()) return false;          // move to perimeter node
  if (!loadInner(iterator)) return false;      // load inner walls
  CEntityLoader entityLoader;                  // init entity loader
  if (!iterator.Next()) return false;          // move to text node
  if (!iterator.Next()) return false;          // move to doors node
  m_Entities = entityLoader.LoadEntities(iterator);
  for (auto& elem : m_Entities) {
    elem.second->InsertIntoMap(mapPtr);
    m_EntitiesVector.push_back(elem.second);
  }
  exportToMap();
  return true;
}

bool CMap::loadPerimeter(CFileLoaderIt iterator) {
  if (iterator.GetName() != "perimeter") {
    throw std::invalid_argument("wrong node");
  }
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
#ifdef DEBUG
  std::cout << "perimeter" << std::endl;
#endif
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    perimeterWalls.push_back(std::make_unique<CWall>(CWall::LoadWall(iterator)));
    m_Heigth = std::max(m_Heigth, perimeterWalls.back()->GetEnd().Y() + 1);
    m_Width = std::max(m_Width, perimeterWalls.back()->GetEnd().X() + 1);
    m_Heigth = std::max(m_Heigth, perimeterWalls.back()->GetStart().Y() + 1);
    m_Width = std::max(m_Width, perimeterWalls.back()->GetStart().X() + 1);
  }
  return true;
}
bool CMap::loadInner(CFileLoaderIt iterator) {
  if (iterator.GetName() != "inner") {
    throw std::invalid_argument("wrong node");
  }
  if (!iterator.Child()) return false;  // move to text node
  if (!iterator.Next()) return false;   // move to first wall node
#ifdef DEBUG
  std::cout << "inner" << std::endl;
#endif
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    innerWalls.push_back(std::make_unique<CWall>(CWall::LoadWall(iterator)));
    if (innerWalls.back()->GetStart().X() > m_Width || innerWalls.back()->GetEnd().X() > m_Width ||
        innerWalls.back()->GetEnd().Y() > m_Heigth || innerWalls.back()->GetStart().Y() > m_Heigth) {
      throw std::invalid_argument("inner wall outside perimeter");
    }
  }
  return true;
}

bool CMap::checkPerimeter() {
  if (!perimeterWalls.front()->Connects(*perimeterWalls.back())) {
    return false;
  }
  size_t numOfWalls = perimeterWalls.size() - 1;
  for (size_t i = 0; i < numOfWalls; ++i) {
    if (!perimeterWalls.at(i)->Connects(*perimeterWalls.at(i + 1))) {
      throw std::invalid_argument("perimeter walls do not create continuous shape");
    }
  }
  return true;
}

std::ostream& operator<<(std::ostream& os, const CMap& room) {
  std::vector<std::vector<std::string>> outputBuffer;
  std::string floor = "\33[47m \33[0m";

  //----print walls  to buffer----
  for (auto& elem : room.perimeterWalls) {
    elem->PrintToBuffer(outputBuffer, floor);
  }
  for (auto& elem : room.innerWalls) {
    elem->PrintToBuffer(outputBuffer, floor);
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
bool CMap::Move(const CCoordinates& start, const CCoordinates& end, int range) {
  int x = end.X();
  int y = end.Y();
  if (x >= m_Width || x < 0 || y >= m_Heigth || y < 0 || m_Map.at(y).at(x) == EMapElem::ENTITY) {
    return false;
  }

  std::queue<std::pair<CCoordinates, int>> toVisit;
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

bool CMap::ExecuteTurns() {
  for (auto& elem : m_EntitiesVector) {
    std::string message = elem->GetName();
    message += "'s turn";
    CInterfaceLocator::getInterface().Message(message);
    Render();
    if (!elem->Turn()) {
      return false;
    }
  }
  return true;
}
void CMap::Render() { m_Game.Render(); }

CMap::CMap(int ID, const std::string& name, CGame& game) : m_ID(ID), m_Name(name), m_Game(game) {}

void CMap::exportToMap() {
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
    if (m_Map.at(coordinate.Y()).at(coordinate.X()) != EMapElem::FLOOR) {
      throw std::invalid_argument("entity cant be on top another");
    }
    m_Map.at(coordinate.Y()).at(coordinate.X()) = EMapElem::ENTITY;
  }
}
std::vector<std::shared_ptr<CEntity>> CMap::EntitiesInRange(const CCoordinates& pos, int range) const {
  std::vector<std::shared_ptr<CEntity>> res;
  std::vector<CCoordinates> resCoordinates;
  // CCordinates and range from start pos
  std::queue<std::pair<CCoordinates, int>> toVisit;
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
EMapElem CMap::isAtPosition(const CCoordinates& pos) const {
  int x = pos.X();
  int y = pos.Y();

  if (x >= m_Width || x < 0 || y >= m_Heigth || y < 0) {
    return EMapElem::FLOOR;
  }
  return m_Map.at(y).at(x);
}
std::vector<std::shared_ptr<CEntity>> CMap::GetLootableEntities(const CCoordinates& pos) const {
  std::vector<std::shared_ptr<CEntity>> entitiesInRange;
  std::vector<std::shared_ptr<CEntity>> res;

  entitiesInRange = EntitiesInRange(pos, LOOT_RANGE);
  for (auto& elem : entitiesInRange) {
    if (elem->IsLootable()) {
      res.push_back(elem);
    }
  }
  return res;
}
bool CMap::Save(CFileLoaderIt it) const {
  if (it.GetName() != "room") {
    return false;
  }

  std::list<std::pair<std::string, std::string>> propList;
  propList.emplace_back("ID", std::to_string(m_ID));
  propList.emplace_back("name", m_Name);
  it.AddProperties(propList);
  it.CreateNewChildNode("perimeter");
  it.CreateNewChildNode("inner");
  it.CreateNewChildNode("entities");
  if (!it.Child()) return false;
  saveWalls(it, perimeterWalls);
  if (!it.Next()) return false;
  saveWalls(it, innerWalls);
  if (!it.Next()) return false;
  return saveEntities(it);
}

bool CMap::saveWalls(CFileLoaderIt it, const std::vector<std::unique_ptr<CWall>>& walls) const {
  for (size_t i = 0; i < walls.size(); ++i) {
    it.CreateNewChildNode("wall");
  }
  it.Child();
  for (auto& elem : walls) {
    elem->Save(it);
    it.Next();
  }
  return true;
}
bool CMap::saveEntities(CFileLoaderIt it) const {
  if (it.GetName() != "entities") {
    return false;
  }
  for (size_t i = 0; i < m_Entities.size(); ++i) {
    it.CreateNewChildNode("entity");
  }
  it.Child();
  for (auto& elem : m_Entities) {
    if (!elem.second->Save(it)) {
      return false;
    }
    if (!it.Next()) return false;
  }
  return true;
}
bool CMap::TransferEntityToRoom(std::shared_ptr<CEntity> entity, const CCoordinates& spawnPoint) {
  if (m_Map.at(spawnPoint.Y()).at(spawnPoint.X()) != EMapElem::FLOOR) {
    throw std::invalid_argument("entity cant be on top another");
  }
  entity->ChangePostion(spawnPoint);
  m_Entities.emplace(spawnPoint, entity);
  return true;
}
