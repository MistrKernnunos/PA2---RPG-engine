//
// Created by machavi on 6/1/21.
//
#pragma once
#include <string>
#include <vector>

#include "CFactory.h"
#include "CFileLoaderIterator.h"
class CItem;
class CHealthPotion;
class CItemLoader {
 public:
  CItemLoader();
  std::vector<std::unique_ptr<CItem>> LoadItems(CFileLoaderIt iterator);

 private:
  CFactory<CItem, std::string, std::unique_ptr<CItem>> m_ItemFactory;
};
