
#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include "Date.h"
#include "Lib.h"
#include "Utils.h"
#include <cstring>
#include <iomanip>

using namespace std;

namespace sdds {

Publication::Publication() {}

void Publication::set(int member_id) {
  if (member_id < 100000 && member_id >= 0) {
    m_membership = member_id;
  }
}
void Publication::setRef(int value) { m_libRef = value; }
void Publication::resetDate() { m_date = Date(); }
char Publication::type() const { return 'P'; }
bool Publication::onLoan() const {
  bool result = false;
  if (m_membership != 0) {
    result = true;
  }
  return result;
}
Date Publication::checkoutDate() const { return m_date; }
bool Publication::operator==(const char *title) const {
  bool result = false;
  if (strstr(m_title, title)) {
    result = true;
  }
  return result;
}
Publication::operator const char *() const { return m_title; }
int Publication::getRef() const { return m_libRef; }
bool Publication::conIO(std::ios &io) const {
  return &io == &cin || &io == &cout;
}

std::ostream &Publication::write(std::ostream &os) const {
  if (conIO(os)) {
    os << "| " << m_shelfId << " | ";
    if (strLen(m_title) > SDDS_TITLE_WIDTH) {
      for (int i = 0; i < SDDS_TITLE_WIDTH; i++) {
        os << m_title[i];
      }
    } else {
      os << setw(30) << left << setfill('.') << m_title;
    }
    os << " | ";
    if (m_membership > 0) {
      os << m_membership;
    } else {
      os << " N/A ";
    }
    os << " | " << m_date << " |";
  } else {
    //os << "\n"
      os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title
       << '\t' << m_membership << '\t' << m_date;
  }
  return os;
}
std::istream &Publication::read(std::istream &is) {

  char tempTitle[256];
  char tempShelf[256];

  delete[] m_title;

  if (conIO(is)) {
    cout << "Shelf No: ";
    is >> tempShelf;
    if (strlen(tempShelf) != SDDS_SHELF_ID_LEN) {
      is.setstate(std::ios::failbit);
    } else {
      strcpy(m_shelfId, tempShelf);
    }
    is.ignore(1000, '\n');

    cout << "Title: ";
    is.getline(tempTitle, 255);

    cout << "Date: ";
    is >> m_date;

    if (!m_date) {
      is.setstate(std::ios::failbit);
    }

  } else {
    is >> m_libRef;
    is.ignore();

    is >> m_shelfId;
    is.ignore();

    is.getline(tempTitle, 255, '\t');

    is >> m_membership;
    is.ignore();

    is >> m_date;

    if (!m_date) {
      is.setstate(std::ios::failbit);
    }
  }
  if (is) {
    m_title = new char[strLen(tempTitle) + 1];
    strCpy(m_title, tempTitle);
  }
  return is;
}
Publication::operator bool() const {
  return m_title && m_title[0] != '\0' && m_shelfId[0] != '\0';
}
Publication::Publication(const Publication &toCopyFrom) { *this = toCopyFrom; }
Publication::~Publication() { delete[] this->m_title; }
Publication &Publication::operator=(const Publication &toCopyFrom) {
  if (this != &toCopyFrom) {
    if (toCopyFrom.m_title) {
      
      strCpy(m_shelfId, toCopyFrom.m_shelfId);
      m_membership = toCopyFrom.m_membership;
      m_libRef = toCopyFrom.m_libRef;
      m_date = toCopyFrom.m_date;
      
      delete[] m_title;
      
      m_title = new char[strLen(toCopyFrom.m_title) + 1];
      strCpy(m_title, toCopyFrom.m_title);
    }
  }
  return *this;
}
} // namespace sdds