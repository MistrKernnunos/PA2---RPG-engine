//
// Created by machavi on 5/29/21.
//
#pragma once
#include "CFileLoaderIterator.h"

class CCordinates {
 public:
  CCordinates() = default;
  CCordinates(int x, int y) : m_X(x), m_Y(y){};
  CCordinates(const CCordinates& other) : m_X(other.m_X), m_Y(other.m_Y){};
  int X() const;
  int Y() const;
  bool Load(CFileLoaderIt iterator);

 private:
  int m_X;
  int m_Y;
};

int CCordinates::X() const { return m_X; }
int CCordinates::Y() const { return m_Y; }

bool CCordinates::Load(CFileLoaderIt iterator) {
  if (!(iterator.GetName() == "X")) {
    throw std::invalid_argument("bad coordinates node name");
    return false;
  }
  m_X = std::stoi(iterator.GetContent());
  iterator.Next();
  iterator.Next();

  if (!(iterator.GetName() == "Y")) {
    throw std::invalid_argument("bad coordinates node name");
    return false;
  }
  m_Y = std::stoi(iterator.GetContent());
  return true;
}