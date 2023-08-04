#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
namespace sdds {
class Menu;
const unsigned int MAX_MENU_ITEMS = 20;
class MenuItem {
  char *m_menuItemContent{nullptr};
  MenuItem(const char * = nullptr);
  // Copy constructor and Copy assignment are deleted
  MenuItem(const MenuItem &) = delete;
  MenuItem &operator=(const MenuItem &) = delete;
  ~MenuItem();
  operator bool() const;
  operator const char *() const;
  std::ostream &display(std::ostream &) const;
  friend class Menu;
};
class Menu {
private:
  char *m_menuTitle{nullptr};
  MenuItem *m_menuItems[MAX_MENU_ITEMS]{nullptr};
  int m_menuItemNumber;

public:
  Menu(const char * = nullptr);

  // Copy constructor and Copy assignment are deleted
  Menu(const Menu &) = delete;
  Menu &operator=(const Menu &) = delete;
  ~Menu();
  char *title() const;
  void displayMenu() const;
  unsigned int run() const;
  unsigned int operator~() const;
  Menu &operator<<(const char *menuitemConent);
  operator int() const;
  operator unsigned int() const;
  operator bool() const;
  const char *operator[](int index) const;
};
std::ostream &operator<<(std::ostream &, const Menu &);
} // namespace sdds
#endif