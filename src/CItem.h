//
// Created by machavi on 5/7/21.
//
#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "CFileLoaderIterator.h"

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
  //  virtual bool Effect(std::shared_ptr<CEntity> toEffect, std::shared_ptr<CEntity> user) = 0;

  virtual bool Load(CFileLoaderIt iterator) = 0;

  friend std::ostream& operator<<(std::ostream& os, const CItem& item);

 private:
  virtual std::ostream& print(std::ostream& out) const = 0;

 protected:
  std::string m_Name;
  size_t m_Size = 0;
};
