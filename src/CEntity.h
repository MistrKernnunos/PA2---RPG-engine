//
//
// Created by machavi on 5/7/21.
//
#pragma once
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "CControler.h"
#include "CCoordinates.h"
#include "CFileLoaderIterator.h"
#include "CGame.h"
#include "CInventory.h"
#include "CMessage.h"
class CRoom;
class CEntity {
 public:
  /**
   * Constructor
   * @param name name of the entity
   */
  CEntity() = default;
  virtual ~CEntity() = default;
  /**
   * executes one turn
   */
  virtual void Turn() = 0;

  /**
   * Facilitates attack action
   * @param toAttack which entity to attack
   * @return true if the attack was successful, false if not (not enough action
   * points, target too far, etc.)
   */
  virtual bool Attack(const CEntity& toAttack) = 0;

  /**
   * entity takes enters defense state until start of next turn
   * @return true if successful, false if not (not enough action points)
   */
  virtual bool Defense() = 0;
  /**
   * handles action if the entity is attacked
   * @param attackPower attack damage of the incoming attack
   * @return the damage that has the entity received
   */
  virtual int Attacked(const int attackDamage) = 0;

  /**
   * loads stats and inventory from file
   * @param it iterator to entity node
   * @return true if successfully loaded otherwise null
   */
  bool Load(CFileLoaderIt it);

  /**
   *moves entity by x and y
   * @param x
   * @param y
   * @return
   */
  virtual bool Move(const int x, const int y) = 0;

  void AttachController(std::shared_ptr<CControler> controler);

  virtual bool RecieveMessage(const CMessage& message) = 0;

  std::vector<std::shared_ptr<CEntity>> getEntitiesInRange(int range) const;

  const std::string& GetName() const;
  size_t GetHeight() const;
  size_t GetWidth() const;
  int GetMaxHealth() const;
  int GetHealth() const;
  int GetDefencePower() const;
  int GetAttackPower() const;
  int GetActionPoints() const;
  int GetXp() const;
  int GetLevel() const;
  const CCoordinates& GetCoordinates() const;

  bool InsertIntoRoom(std::weak_ptr<CRoom> room);

  //  CInventory& GetInventory();

  //  const CInventory& GetInventory() const;

  void PrintToBuffer(std::vector<std::vector<std::string>>& outputBuffer);

  friend std::ostream& operator<<(std::ostream& os, const CEntity& entity);

 private:
  bool loadProperties(CFileLoaderIt iterator);

 protected:
  // information about the entity
  std::string m_Name;
  size_t m_Height = 1;
  size_t m_Width = 1;
  int m_MaxHealth = 0;
  int m_NextLevelCoef = 5;
  int m_Movement = 0;

  // current stats of the entity
  int m_Health = 0;
  int m_DefencePower = 0;
  int m_AttackPower = 0;
  int m_ActionPoints = 0;
  int m_XP = 0;
  int m_Level = 1;
  std::shared_ptr<CControler> m_Controller;

  std::weak_ptr<CRoom> m_Room;
  CCoordinates m_Coordinates;
  CInventory m_Inventory;
  static std::string m_Apperance;
};
