//
// Created by machavi on 6/1/21.
//
#include "CItemLoader.h"

#include "CHealthPotion.h"
CItemLoader::CItemLoader() { m_ItemFactory.Register("healthPotion", CHealthPotion::Create); }

std::vector<std::unique_ptr<CItem>> CItemLoader::LoadItems(CFileLoaderIt iterator) {
  std::vector<std::unique_ptr<CItem>> items;
  if (iterator.GetName() != "items") {
    throw std::invalid_argument("wrong item node");
    return items;
  }

  iterator.Child();  // go to item node
  iterator.Next();
  for (; iterator.Valid(); iterator.Next(), iterator.Next()) {
    auto prop = iterator.GetProperties();
    if (prop.empty() || prop.size() != 1 || prop.front().first != "itemID") {
      throw std::invalid_argument("wrong item node ");
      return items;
    }
    items.push_back(m_ItemFactory.createObject(prop.front().second));
    if (!items.back()) {
      auto end = items.end();
      items.erase(--end);
      return items;
    }
    if (!items.back()->Load(iterator)) {
      items.erase(items.end() - 1);
      throw std::invalid_argument("error during item loading");
      return items;
    }

#ifdef DEBUG
    std::cout << *(items.back());
    std::cout << std::endl;
#endif
  }
  return items;
}