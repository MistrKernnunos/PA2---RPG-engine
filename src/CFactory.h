//
// Created by machavi on 5/30/21.
//
#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>

template <class absClass, typename identifier, class retType = std::shared_ptr<absClass>,
          class maker = std::function<retType(void)>>
class CFactory {
 public:
  CFactory() = default;
  bool Register(const std::string& id, maker creator);

  bool UnRegister(const identifier& id);

  retType createObject(const identifier& id);

 private:
  std::map<identifier, maker> m_IdClassCreator;
};
template <class absClass, typename identifier, typename retType, class maker>
bool CFactory<absClass, identifier, retType, maker>::Register(const std::string& id, maker creator) {
  auto res = m_IdClassCreator.insert(std::make_pair(id, creator));
  return res.second;
}
template <class absClass, typename identifier, typename retType, class maker>
bool CFactory<absClass, identifier, retType, maker>::UnRegister(const identifier& id) {
  return m_IdClassCreator.erase(id) == 1;
}
template <class absClass, typename identifier, typename retType, class maker>
retType CFactory<absClass, identifier, retType, maker>::createObject(const identifier& id) {
  auto found = m_IdClassCreator.find(id);
  if (found == m_IdClassCreator.end()) {
    throw std::invalid_argument("wrong entity type");
    return nullptr;
  }
  maker creator = found->second;
  retType res = creator();
  return res;
}
