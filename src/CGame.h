//
// Created by machavi on 6/2/21.
//
#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "CCoordinates.h"
#include "CFileLoader.h"
#include "CFileLoaderIterator.h"
#include "CInterface.h"
class CRoom;
class CGame {
 public:
  CGame(const CInterface &interface) : m_Interface(interface){};
  CGame(const CGame &) = delete;
  CGame &operator=(const CGame &) = delete;

  //  bool LoadGame();

  bool LoadMap(const std::string &path);

  bool Save() const;

  bool Start();

  bool IsInitialized() const;

  void Erase();
  /**
   * checks whether it is possible to get from start to end in range steps
   * @param start position
   * @param end position
   * @param range max number of steps
   * @return true if it can be traversed in range steps or false if not
   */

  void Render();

 private:
  bool loadSpawnPoint(CFileLoaderIt it);
  bool saveSpawnPoint(CFileLoaderIt it) const;

  CInterface m_Interface;
  std::map<int, std::shared_ptr<CRoom>> m_Rooms;
  int m_spawnRoomID = 0;
  std::string m_Name;
  CCoordinates m_SpawnPoint;
  bool m_Initialized = false;
  int m_CurrRoomID = 0;
};
