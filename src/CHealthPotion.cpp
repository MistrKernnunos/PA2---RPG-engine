//
// Created by machavi on 6/1/21.
//

#include "CHealthPotion.h"
std::unique_ptr<CItem> CHealthPotion::Create() { return std::make_unique<CHealthPotion>(); }

bool CHealthPotion::Load(CFileLoaderIt iterator) {
  if (iterator.GetName() != "item") {
    throw std::invalid_argument("wrong item node");
    return false;
  }
  iterator.Child();
  iterator.Next();
  m_Name = iterator.GetContent("name");
  iterator.Next(2);
  m_HealingStrength = std::stoi(iterator.GetContent("healing"));
  iterator.Next(2);
  m_Size = std::stoul(iterator.GetContent("size"));
  return true;
}
std::ostream& CHealthPotion::print(std::ostream& out) const {
  out << "m_HealingStrength: " << m_HealingStrength;
  out << " m_Name: " << m_Name << " m_Size: " << m_Size;
  return out;
}
