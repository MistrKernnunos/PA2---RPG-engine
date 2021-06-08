//
// Created by machavi on 5/30/21.
//
#pragma once
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
/**
 * abstract class factory
 * @tparam absClass
 * @tparam identifier
 * @tparam retType return type
 * @tparam maker
 */
template <class absClass, typename identifier, class retType = std::shared_ptr<absClass>,
          class maker = std::function<retType(void)>>
class CFactory {
 public:
  CFactory() = default;
  /**
   * registers entity to the factory
   * @param id identifier of the entity
   * @param creator function that returns the entity
   * @return true if successful
   */
  bool Register(const std::string& id, maker creator);
  /**
   * unregisters entity
   * @param id identifier of the entity
   * @return true if successful
   */
  bool UnRegister(const identifier& id);

  /**
   * returns entity according to identifier
   * @param id identifier of entity to create
   * @return created entity
   */
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
    throw std::invalid_argument("wrong object type");
  }
  maker creator = found->second;
  retType res = creator();
  return res;
}
