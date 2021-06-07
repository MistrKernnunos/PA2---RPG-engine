//
// Created by machavi on 6/4/21.
//
#include "CWeapon.h"

#include "CEntity.h"
bool CWeapon::Load(CFileLoaderIt it) {
  if (it.GetName() != "weapon") {
    throw std::invalid_argument("wrong item node");
  }
  if (!it.Child()) return false;
  if (!it.Next()) return false;
  m_Name = it.GetContent("name");
  if (!it.Next(2)) return false;
  m_Range = std::stoi(it.GetContent("range"));
  if (!it.Next(2)) return false;
  m_AttackPower = std::stoi(it.GetContent("attackPower"));
  if (!it.Next(2)) return false;
  m_DefensePower = std::stoi(it.GetContent("defensePower"));
  if (!it.Next(2)) return false;
  m_Size = std::stoul(it.GetContent("size"));
  return true;
}
std::ostream& operator<<(std::ostream& os, const CWeapon& weapon) {
  os << "m_Name: " << weapon.m_Name << " m_Range: " << weapon.m_Range << " m_AttackPower: " << weapon.m_AttackPower
     << " m_DefensePower: " << weapon.m_DefensePower << " m_Size: " << weapon.m_Size;
  return os;
}
const std::string& CWeapon::GetName() const { return m_Name; }
int CWeapon::GetRange() const { return m_Range; }
int CWeapon::GetAttackPower() const { return m_AttackPower; }
int CWeapon::GetDefensePower() const { return m_DefensePower; }
size_t CWeapon::GetSize() const { return m_Size; }
bool CWeapon::Save(CFileLoaderIt it) const {
  if (it.GetName() != "weapon") {
    return false;
  }
  if (!addEntityID(it)) return false;
  if (!it.CreateNewTextChildNode("name", m_Name)) return false;
  if (!it.CreateNewTextChildNode("range", std::to_string(m_Range))) return false;
  if (!it.CreateNewTextChildNode("attackPower", std::to_string(m_AttackPower))) return false;
  if (!it.CreateNewTextChildNode("defensePower", std::to_string(m_DefensePower))) return false;
  return it.CreateNewTextChildNode("size", std::to_string(m_Size));
}
