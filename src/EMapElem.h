//
// Created by machavi on 5/9/21.
//
#include <iostream>
#pragma once

enum class EMapElem{
  FLOOR = ' '
  WALL = '#'
  DOOR = '|'
};

std::ostream & operator<< ( std::ostream & out, EMapElem elem );

std::istream & operator>> ( std::istream & in, EMapElem & elem );