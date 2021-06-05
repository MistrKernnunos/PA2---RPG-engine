//
// Created by machavi on 6/1/21.
//
#pragma once
#include <memory>
#include <ostream>

#include "CEntity.h"
#include "CFileLoaderIterator.h"
#include "CItem.h"

class CHealthPotion : public CItem {
 public:
  CHealthPotion() = default;
  ~CHealthPotion() = default;

      bool Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) override;

  static std::unique_ptr<CItem> Create();

  bool Load(CFileLoaderIt iterator);

  std::string PrintToString() override;

 private:
  std::ostream& print(std::ostream& out) const override;


 private:
  int m_HealingStrength = 0;
};

