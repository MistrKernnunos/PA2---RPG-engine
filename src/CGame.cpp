//
// Created by machavi on 5/7/21.
//

#include "CGame.h"

#include "CFileLoader.h"
#include "CFileLoaderIterator.h"
#include "CRoom.h"

bool CGame::LoadMap(const std::string &path) {
  CFileLoader loader;
  if (!loader.loadXmlFile(path)) {
    throw std::invalid_argument("cant open map file");
    return false;
  }

  auto it = loader.GetNode("spawnPoint");
  if (!loadSpawnPoint(it)) {
    return false;
  }

  it = loader.GetNode("rooms");
  it.Child();  // move to room node
  it.Next();

  for (; it.Valid(); it.Next(2)) {
    auto prop = it.GetProperties();
    if (prop.size() != 2 || prop.front().first != "ID" || prop.back().first != "name") {
      throw std::invalid_argument("bad room properties");
      return false;
    }
    int ID = std::stoi(prop.front().second);

    if (m_Rooms.count(ID) == 1) {
      throw std::invalid_argument("rooms with duplicate IDs");
      return false;
    }

    auto room = std::make_shared<CRoom>(ID, prop.back().second, *this);

    if (!room->Load(it, room)) {
      return false;
    }
    m_Rooms.insert(std::make_pair(ID, room));

#ifdef DEBUG
    std::cout << *room << std::endl;
#endif
  }
  if (m_Rooms.size() == 0) {
    throw std::invalid_argument("no rooms in map");
    return false;
  }
  if (m_Rooms.count(m_spawnRoomID) != 1) {
    throw std::invalid_argument("spawn room not present in map");
    return false;
  }
  m_Initialized = true;
  return true;
}
bool CGame::IsInitialized() const { return m_Initialized; }

bool CGame::loadSpawnPoint(CFileLoaderIt it) {
  if (it.GetName() != "spawnPoint") {
    throw std::invalid_argument("wrong node");
    return false;
  }
  it.Child();  // go to the child node
  it.Next();
  m_spawnRoomID = std::stoi(it.GetContent("roomID"));
  m_CurrRoomID = m_spawnRoomID;
  it.Next(2);
  return m_SpawnPoint.Load(it);
}
void CGame::Erase() {
  m_Rooms.clear();
  m_spawnRoomID = 1;
  m_Initialized = false;
  m_SpawnPoint = CCoordinates(0, 0);
}
void CGame::Render() {
  auto room = m_Rooms.at(m_CurrRoomID);
  m_Interface.Print(*room);
}
bool CGame::Start() {
  while (true) {
    m_Rooms.at(m_CurrRoomID)->ExecuteTurns();
  }
}
