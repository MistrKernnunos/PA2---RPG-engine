//
// Created by machavi on 5/7/21.
//

#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <utility>

class CInterface {
 public:
  CInterface(std::ostream& out, std::istream& in) : m_Out(out), m_In(in) {}

  template <class returnType>
  returnType PromtWithMessage(const std::string& message) const;

  void Message(const std::string& message) const;

  template <class T>
  std::ostream& Print(const T& toPrint);

 private:
  std::ostream& m_Out;
  std::istream& m_In;
};
template <class returnType>
returnType CInterface::PromtWithMessage(const std::string& message) const {
  returnType res;
  m_Out << message << std::endl;
  while (!(m_In >> res) && !m_In.eof()) {
    Message("Wrong input, enter again🙄");
    m_In.clear();  // clear input
    m_In.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return res;
}
template <class T>
std::ostream& CInterface::Print(const T& toPrint) {
  m_Out << toPrint << std::endl;
  return m_Out;
}