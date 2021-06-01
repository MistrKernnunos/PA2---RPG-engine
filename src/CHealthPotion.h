//
// Created by machavi on 6/1/21.
//
#pragma once
#include <memory>
#include <ostream>

#include "CEntity.h"
#include "CItem.h"

class CHealthPotion : public CItem {
 public:
  CHealthPotion() = default;
  ~CHealthPotion() = default;
  //    bool Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) override;

  static std::unique_ptr<CItem> Create();

  bool Load(CFileLoaderIt iterator);

 private:
  std::ostream& print(std::ostream& out) const override;

 public:
  friend std::ostream& operator<<(std::ostream& os, const CHealthPotion& potion);

 private:
  int m_HealingStrength = 0;
};

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
