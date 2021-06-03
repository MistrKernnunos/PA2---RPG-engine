//
// Created by machavi on 5/7/21.
//
#include "CItem.h"
 std::ostream& operator<<(std::ostream& os, const CItem& item) {
  item.print(os);
  return os;
}
