//
// Created by machavi on 6/2/21.
//
#include "CEntity.h"

#include "CInventory.h"
#include "CRoom.h"

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
const CInventory& CEntity::GetInventory() const { return m_Inventory; }

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
  m_DefenseCost = std::stoi(iterator.GetContent("defenseCost"));
  iterator.Next(2);
  return true;
}
void CEntity::AttachController(std::shared_ptr<CControler> controler) { m_Controller = controler; }
bool CEntity::InsertIntoRoom(std::weak_ptr<CRoom> room) { m_Room = room;}

std::vector<std::shared_ptr<CEntity>> CEntity::GetEntitiesInRange(int range) const {
  return m_Room.lock()->EntitiesInRange(m_Coordinates, range);
}
std::ostream& operator<<(std::ostream& os, const CEntity& entity) {
  os << "m_Name: " << entity.m_Name;
  return os;
}
int CEntity::GetMovementCost() const { return m_MovementCost; }
int CEntity::GetAttackCost() const { return m_AttackCost; }
int CEntity::GetDefenseConst() const { return m_DefenseCost; }
int CEntity::GetCurrActionPoints() const { return m_CurrActionPoints; }
state CEntity::GetState() const { return m_State; }

bool CEntity::IsLootable() { return m_Lootable; }
void CEntity::SetHealth(int mHealth) { m_Health = mHealth; }
CInventory& CEntity::GetEditableInventory() { return m_Inventory; }
std::vector<std::shared_ptr<CEntity>> CEntity::GetLootableEntities() const {
  return m_Room.lock()->GetLootableEntities(m_Coordinates);
}

bool CEntity::Save(CFileLoaderIt it) {
  if (it.GetName() != "entity") {
    return false;
  }
  if (!addEntityId(it)) return false;
  if (!it.CreateNewChildNode("properties")) return false;
  if (!it.CreateNewChildNode("coordinates")) return false;
  if (!it.CreateNewChildNode("inventory")) return false;
  it.Child();
  saveProperties(it);
  it.Next();
  m_Coordinates.Save(it);
  it.Next();
  m_Inventory.Save(it);
}
bool CEntity::saveProperties(CFileLoaderIt it) {
  if (it.GetName() != "properties") {
    return false;
  }
  it.CreateNewTextChildNode("name", m_Name);
  it.CreateNewTextChildNode("maxHealth", std::to_string(m_MaxHealth));
  it.CreateNewTextChildNode("health", std::to_string(m_Health));
  it.CreateNewTextChildNode("attack", std::to_string(m_AttackPower));
  it.CreateNewTextChildNode("defense", std::to_string(m_DefencePower));
  it.CreateNewTextChildNode("actionPoints", std::to_string(m_ActionPoints));
  it.CreateNewTextChildNode("xp", std::to_string(m_XP));
  it.CreateNewTextChildNode("level", std::to_string(m_Level));
  it.CreateNewTextChildNode("movement", std::to_string(m_Movement));
  it.CreateNewTextChildNode("levelCoef", std::to_string(m_NextLevelCoef));
  it.CreateNewTextChildNode("movementCost", std::to_string(m_MovementCost));
  it.CreateNewTextChildNode("attackCost", std::to_string(m_AttackCost));
  it.CreateNewTextChildNode("defenseCost", std::to_string(m_DefenseCost));
  return true;
}
