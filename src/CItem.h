//
// Created by machavi on 5/7/21.
//
#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "CFileLoaderIterator.h"
class CEntity;

class CItem {
 public:
  CItem() = default;
  virtual ~CItem() = default;

  /**
   * performs effect of this item
   * @param toEffect entity which this item effects
   * @param user entity which uses this item
   * @return if the effect was used successfully
   */
  virtual bool Effect(CEntity& toEffect, CEntity& user) = 0;

  virtual bool Load(CFileLoaderIt iterator) = 0;

  friend std::ostream& operator<<(std::ostream& os, const CItem& item);

  const std::string& GetName() const;
  size_t GetSize() const;

  virtual std::string PrintToString() = 0;

  virtual std::ostream& print(std::ostream& out) const = 0;

 protected:
  std::string m_Name;
  size_t m_Size = 0;
};
