//
// Created by machavi on 6/1/21.
//
#pragma once
#include <memory>
#include <ostream>

#include "CFileLoaderIterator.h"
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

