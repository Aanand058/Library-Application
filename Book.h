

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include "Publication.h"
namespace sdds {

class Book : public Publication {
  char *m_authorsName{nullptr};

public:
  Book();

  char type() const;

  std::ostream &write(std::ostream &os) const;

  std::istream &read(std::istream &is);

  virtual void set(int member_id);

  operator bool() const;

  // Rule of three
  Book(const Book &toCopyFrom);
  Book &operator=(const Book &toCopyFrom);
  ~Book();
};

} // namespace sdds
#endif
