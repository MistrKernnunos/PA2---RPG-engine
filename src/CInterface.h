//
// Created by machavi on 5/7/21.
//

#pragma once
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

class CInterface {
 public:
  CInterface(std::ostream& out, std::istream& in) : m_Out(out), m_In(in) {
    m_In.exceptions(std::ios_base::eofbit | std::ios_base::badbit);
    m_In.exceptions(std::ios_base::eofbit | std::ios_base::badbit | std::ios_base::failbit);
  }

  template <class returnType>
  returnType PromtWithMessage(const std::string& message) const;

  template <class returnType1, class returnType2>
  std::pair<returnType1, returnType2> PromtWithMessage(const std::string& message) const;

  void Message(const std::string& message) const;

  template <class T>
  std::ostream& Print(const T& toPrint);

  /**
   * shows user message and expects number input from 0 to number of choices
   * @param message message to show
   * @param numberOfChoices number of choices user has
   * @return chosen choice
   */
  int Chooser(const std::string& message, int numberOfChoices);

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
    m_In.ignore();
  }
  return res;
}
template <class returnType1, class returnType2>
std::pair<returnType1, returnType2> CInterface::PromtWithMessage(const std::string& message) const {
  returnType1 res1;
  returnType2 res2;
  m_Out << message << std::endl;
  bool state = false;
  for (std::string line; !state && std::getline(m_In >> std::ws, line);) {
    bool load1 = false;
    bool load2 = false;
    std::istringstream iss;
    iss.str(line);
    if (iss >> res1) {
      load1 = true;
    }
    if (iss >> res2) {
      load2 = true;
    } else {
      load2 = true;
      res2 = 0;
    }
    if (load1 && load2 && iss.eof()) {
      state = true;
    } else {
      Message("Wrong input, enter again🙄");
    }
  }
  return std::make_pair(res1, res2);
}
template <class T>
std::ostream& CInterface::Print(const T& toPrint) {
  m_Out << toPrint << std::endl;
  return m_Out;
}
