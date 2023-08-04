#define _CRT_SECURE_NO_WARNINGS
#include "Streamable.h"

namespace sdds {

std::ostream &operator<<(std::ostream &os, const Streamable &rhs) {
  if (rhs) {
    rhs.write(os);
  }
  return os;
}
std::istream &operator>>(std::istream &is, Streamable &rhs) {
  return rhs.read(is);
}

Streamable::~Streamable(){};
} // namespace sdds