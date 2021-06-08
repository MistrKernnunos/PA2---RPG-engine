//
// Created by machavi on 6/2/21.
//
#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "CCoordinates.h"
#include "CEntity.h"
#include "CFileLoader.h"
#include "CFileLoaderIterator.h"
#include "CInterface.h"
enum toLoad { GAME, MAP };
class CMap;
class CGame {
 public:
  CGame(const CInterface &interface) : m_Interface(interface){};
  CGame(const CGame &) = delete;
  CGame &operator=(const CGame &) = delete;

  /**
   * loads map
   * @param path path to map file
   * @return true if successful
   */
  bool LoadMap(const std::string &path, toLoad what = MAP);
  /**
   * saves game
   * @return true if successful
   */
  bool Save() const;

  /**
   * starts the game
   */
  void Start();
  /**
   * gives player choice to save game or to end without saving
   */
  void EndGame();

  bool IsInitialized() const;

  /**
   * clears the game
   */
  void Erase();
  /**
   * checks whether it is possible to get from start to end in range steps
   * @param start position
   * @param end position
   * @param range max number of steps
   * @return true if it can be traversed in range steps or false if not
   */

  /**
   * renders game on screen
   */
  void Render();

  /**
   * inserts player on spawn point
   * @param player player to insert
   * @return true if successful, false if not
   */
  bool SpawnPlayer(std::shared_ptr<CEntity> player);

 private:
  bool loadSpawnPoint(CFileLoaderIt it);
  bool saveSpawnPoint(CFileLoaderIt it) const;

  CInterface m_Interface;
  std::map<int, std::shared_ptr<CMap>> m_Rooms;
  int m_spawnRoomID = 0;
  std::string m_Name;
  CCoordinates m_SpawnPoint;
  bool m_Initialized = false;
  int m_CurrRoomID = 0;
};
