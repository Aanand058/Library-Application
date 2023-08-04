

#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H
#include "Date.h"
#include "Lib.h"
#include "Streamable.h"
namespace sdds {

class Publication : public Streamable {
  char *m_title{nullptr};
  char m_shelfId[5]{};
  int m_membership{0};
  int m_libRef{0};

  Date m_date{};

public:
  Publication();

  virtual void set(int member_id);

  void setRef(int value);

  void resetDate();

  virtual char type() const;

  bool onLoan() const;

  Date checkoutDate() const;

  bool operator==(const char *title) const;

  operator const char *() const;

  int getRef() const;

  bool conIO(std::ios &io) const;

  std::ostream &write(std::ostream &os) const;
  std::istream &read(std::istream &is);

  operator bool() const;

  // Rule of three
  Publication(const Publication &toCopyFrom);
  Publication &operator=(const Publication &toCopyFrom);
  ~Publication();

  void setEmpty();
};

} // namespace sdds
#endif