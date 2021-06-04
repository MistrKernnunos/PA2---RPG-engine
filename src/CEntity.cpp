//
// Created by machavi on 6/2/21.
//
#include "CInventory.h"
#include "CRoom.h"
std::string CEntity::m_Apperance = "\33[105m*\33[0m";

const std::string& CEntity::GetName() const { return m_Name; }
size_t CEntity::GetHeight() const { return m_Height; }
size_t CEntity::GetWidth() const { return m_Width; }
int CEntity::GetMaxHealth() const { return m_MaxHealth; }
int CEntity::GetHealth() const { return m_Health; }
int CEntity::GetDefencePower() const { return m_DefencePower; }
int CEntity::GetAttackPower() const { return m_AttackPower; }
int CEntity::GetActionPoints() const { return m_ActionPoints; }
int CEntity::GetXp() const { return m_XP; }
int CEntity::GetLevel() const { return m_Level; }
const CCoordinates& CEntity::GetCoordinates() const { return m_Coordinates; }
void CEntity::PrintToBuffer(std::vector<std::vector<std::string>>& outputBuffer) {
  outputBuffer.at(m_Coordinates.Y()).at(m_Coordinates.X()) = m_Apperance;
}
// const CInventory& CEntity::GetInventory() const { return m_Inventory; }
// CInventory& CEntity::GetInventory() { return m_Inventory; }

// bool CEntity::InsertIntoRoom(std::shared_ptr<CRoom> room) { return false; }

bool CEntity::Load(CFileLoaderIt iterator) {
  if (iterator.GetName() != "entity") {
    throw std::invalid_argument("wrong entity node");
    return false;
  }
  iterator.Child();
  iterator.Next();
  if (!loadProperties(iterator)) return false;
  iterator.Next();
  iterator.Next();
  if (!(m_Coordinates.Load(iterator))) return false;
  iterator.Next();
  iterator.Next();
  if (!(m_Inventory.Load(iterator))) return false;
  return true;
}

bool CEntity::loadProperties(CFileLoaderIt iterator) {
  if (iterator.GetName() != "properties") {
    throw std::invalid_argument("wrong property node");
    return false;
  }
  iterator.Child();
  iterator.Next();
  m_Name = iterator.GetContent("name");
  iterator.Next(2);
  m_MaxHealth = std::stoi(iterator.GetContent("maxHealth"));
  iterator.Next(2);
  m_Health = std::stoi(iterator.GetContent("health"));
  iterator.Next(2);
  m_AttackPower = std::stoi(iterator.GetContent("attack"));
  iterator.Next(2);
  m_DefencePower = std::stoi(iterator.GetContent("defense"));
  iterator.Next(2);
  m_ActionPoints = std::stoi(iterator.GetContent("actionPoints"));
  iterator.Next(2);
  m_XP = std::stoi(iterator.GetContent("xp"));
  iterator.Next(2);
  m_Level = std::stoi(iterator.GetContent("level"));
  iterator.Next(2);
  m_Movement = std::stoi(iterator.GetContent("movement"));
  iterator.Next(2);
  m_NextLevelCoef = std::stoi(iterator.GetContent("levelCoef"));
  iterator.Next(2);
  m_MovementCost = std::stoi(iterator.GetContent("movementCost"));
  iterator.Next(2);
  m_AttackCost = std::stoi(iterator.GetContent("attackCost"));
  iterator.Next(2);
  m_DefenseConst = std::stoi(iterator.GetContent("defenseCost"));
  return true;
}
void CEntity::AttachController(std::shared_ptr<CControler> controler) { m_Controller = controler; }
bool CEntity::InsertIntoRoom(std::weak_ptr<CRoom> room) { m_Room = room; }

std::vector<std::shared_ptr<CEntity>> CEntity::getEntitiesInRange(int range) const {
  return m_Room.lock()->PossibleToAttack(m_Coordinates, range);
}
std::ostream& operator<<(std::ostream& os, const CEntity& entity) {
  os << "m_Name: " << entity.m_Name;
  return os;
}
int CEntity::GetMovementCost() const { return m_MovementCost; }
int CEntity::GetAttackCost() const { return m_AttackCost; }
int CEntity::GetDefenseConst() const { return m_DefenseConst; }
int CEntity::GetCurrActionPoints() const { return m_CurrActionPoints; }
