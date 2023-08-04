
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "Utils.h"
#include <iomanip>
using namespace std;
namespace sdds {
MenuItem::MenuItem(const char *content) {
  if (content && content[0] != '\0') {
    m_menuItemContent = new char[strLen(content) + 1];
    strCpy(m_menuItemContent, content);
  } else {
    m_menuItemContent = nullptr;
  }
}
MenuItem::~MenuItem() { delete[] m_menuItemContent; }
MenuItem::operator bool() const { return m_menuItemContent != nullptr; }
MenuItem::operator const char *() const { return m_menuItemContent; }
ostream &MenuItem::display(ostream &os) const {
  if (m_menuItemContent && m_menuItemContent[0] != '\0')
    os << m_menuItemContent;
  return os;
}
Menu::Menu(const char *title) {
  if (title && title[0] != '\0') {
    m_menuTitle = new char[strLen(title) + 1];
    strCpy(m_menuTitle, title);
    m_menuItemNumber = 0;
  } else {
    m_menuTitle = nullptr;
    m_menuItemNumber = 0;
  }
}
Menu::~Menu() {
  delete[] m_menuTitle;
  m_menuTitle = nullptr;
  for (int i = 0; i < m_menuItemNumber; i++) {
    delete m_menuItems[i];
    m_menuItems[i] = nullptr;
  }
}
char *Menu::title() const {
  char *res = nullptr;
  if (m_menuTitle && m_menuTitle[0] != '\0')
    res = m_menuTitle;
  return res;
}
void Menu::displayMenu() const {
  if (title()) {
    cout << title();
    cout << "\n";
  }

  for (int i = 0; i < m_menuItemNumber; i++) {
    cout.setf(ios::right);
    cout.width(2);
    cout << (i + 1) << "- " << m_menuItems[i]->m_menuItemContent << endl;
  }
  cout << " 0- Exit" << endl;
  cout << "> ";
}
unsigned int Menu::run() const {
  displayMenu();
  return getIntRange(0, m_menuItemNumber);
}
unsigned int Menu::operator~() const { return run(); }
Menu &Menu::operator<<(const char *menuitemConent) {
  if (m_menuItemNumber < int(MAX_MENU_ITEMS)) {
    m_menuItems[m_menuItemNumber] = new MenuItem(menuitemConent);
    m_menuItemNumber++;
  }
  return *this;
}
Menu::operator int() const { return m_menuItemNumber; }
Menu::operator unsigned int() const { return m_menuItemNumber; }
Menu::operator bool() const { return m_menuItemNumber > 0; }
ostream &operator<<(ostream &os, const Menu &M) {
  if (M.title())
    os << M.title();
  return os;
}
const char *Menu::operator[](int index) const {
  const char *res = nullptr;
  index = index % m_menuItemNumber;
  if (index > -1)
    res = m_menuItems[index]->m_menuItemContent;
  return res;
}
} // namespace sdds