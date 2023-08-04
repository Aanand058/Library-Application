
#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include "Utils.h"
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

namespace sdds {

Book::Book() : Publication() { this->m_authorsName = nullptr; }

Book::Book(const Book &toCopyFrom) { *this = toCopyFrom; }

Book::~Book() {
  delete[] this->m_authorsName;
  this->m_authorsName = nullptr;
}

Book &Book::operator=(const Book &toCopyFrom) {
  if (this != &toCopyFrom) {
    Publication::operator=(toCopyFrom);
    if (toCopyFrom.m_authorsName) {
      delete[] this->m_authorsName;
      this->m_authorsName = new char[strLen(toCopyFrom.m_authorsName) + 1];
      strCpy(this->m_authorsName, toCopyFrom.m_authorsName);
    }
  }
  return *this;
}

char Book::type() const { return 'B'; }

std::ostream &Book::write(std::ostream &os) const {
  char temp[SDDS_AUTHOR_WIDTH + 1]{};

  strncpy(temp, m_authorsName, SDDS_AUTHOR_WIDTH);

  Publication::write(os);

  if (conIO(os)) {
    os << ' ';
    if (strLen(m_authorsName) > SDDS_AUTHOR_WIDTH) {
      os << setw(SDDS_AUTHOR_WIDTH);
      os << left;
      os << temp;
    } else {
      os << setw(SDDS_AUTHOR_WIDTH);
      os << left;
      os << m_authorsName;
    }
    os << " |";
  } else {
    os << '\t' << m_authorsName;
  }
  return os;
}

std::istream &Book::read(std::istream &is) {
  char authName[256] = {0};

  Publication::read(is);

  if (conIO(is)) {
    is.ignore();
    cout << "Author: ";
  } else {
    is.ignore(1000, '\t');
  }

  is.get(authName, 256);
  if (m_authorsName) {
    delete[] m_authorsName;
    m_authorsName = nullptr;
  }
  if (is) {
    m_authorsName = new char[strlen(authName) + 1];
    strCpy(m_authorsName, authName);
  }

  return is;
}

void Book::set(int memberId) {
  Publication::set(memberId);
  Publication::resetDate();
}

Book::operator bool() const {
  bool result = false;
  if (m_authorsName && m_authorsName[0] != '\0') {
    result = true;
  }
  return Publication::operator bool() && result;
}
} // namespace sdds
