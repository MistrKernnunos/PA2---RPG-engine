//
// Created by machavi on 5/7/21.
//
#include <string>

#include "CEntity.h"

#ifndef MACHAVI4_CITEM_H
#define MACHAVI4_CITEM_H
class CItem {
 public:
  CItem(const string& name, const size_t size) : m_Name(name), m_Size(size) {}

  /**
   * performs effect of this item
   * @param toEffect entity which this item effects
   * @param user entity which uses this item
   * @return if the effect was used successfully
   */
  virtual bool Effect(std::shared_ptr<CEntity> toEffect,
                      std::shared_ptr<CEntity> user) = 0;

 private:
  string m_Name;
  size_t m_Size;
};

#endif  // MACHAVI4_CITEM_H
