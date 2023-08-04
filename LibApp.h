#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Book.h"
#include "Lib.h"
#include "Menu.h"
#include "PublicationSelector.h"
#include "Streamable.h"

namespace sdds {
class LibApp {
  bool m_changed{false};
  Menu m_mainMenu{};
  Menu m_exitMenu{};
  // MS5 Updates
  char m_fileName[256]{};
  Publication *m_ppa[SDDS_LIBRARY_CAPACITY]{nullptr};
  int m_nolp{0};
  int m_llrn{0};
  Menu m_pubType{0};

  bool confirm(const char *message);

  void load();
  void save();
  int search(int search);

  void returnPub();

  void newPublication();
  void removePublication();
  void checkOutPub();
  Publication *getPub(int libRef);

public:
  // LibApp();
  LibApp(const char *filename);
  ~LibApp();
  void run();
  // MS5
};
} // namespace sdds
#endif
