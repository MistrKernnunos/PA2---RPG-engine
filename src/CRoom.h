//
// Created by machavi on 5/7/21.
//

#include <memory>
#include <vector>

#include "CEntity.h"
#include "CInterface.h"
#include "EMapElem.h"

#pragma once

class CRoom {
 public:
  CRoom() = default;

  bool Load(const std::string& filename);

  bool Save(const std::string& filename) const;

  /**
   * executes turns for all entites in room
   */
  void ExecuteTurns();
  /**
   * transfers entity to this room
   * @param entity which entity to this room
   * @param doorNumber number of door to which entity arrives
   * @return true if succeeded, else if not
   */
  bool TransferEntityToRoom(std::shared_ptr<CEntity> entity,
                            unsigned int doorNumber);
  /**
   * transfers entity from this room to dest room
   * @param dest room where to transfer the entity
   * @param entity entity which to transfer
   * @param doorNumber which door is used
   * @return true if succeeded, else if not
   */
  bool TransferEntityFromRoom(std::shared_ptr<CRoom> dest,
                              std::shared_ptr<CEntity> entity,
                              usingned int doorNumber);
  /**
   * prints room to the interface
   * @param interface interface to print through
   */
  void Print(const CInterface& interface);

 private:
  std::vector<std::vector<EMapElem>> m_Map;  // map of the room
  std::vector<std::unique_ptr<CEntity>>
      m_Entities;  // entities present in the room
  std::vector<std::pair<std::shared_ptr<CRoom>, unsigned int>>
      m_ConnectedRooms;  // index is door which this connection belong to,
                         // pointer to room which connect and door number
};
