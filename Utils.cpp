
#include <iostream>
using namespace std;
#include "Utils.h"
namespace sdds {

void strCpy(char *des, const char *src) {
  int i;
  for (i = 0; i < strLen(src); i++) {
    des[i] = src[i];
  }
  des[i] = '\0';
}

int strLen(const char *s) {
  int i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}

int getInt() {
  int x;
  cin >> x;
  while (cin.fail() || cin.get() != '\n') {
    if (cin.fail())
      cout << "Invalid Selection, try again: ";
    cin.clear();
    cin.ignore(10000, '\n');
    cin >> x;
  }
  return x;
}
int getIntRange(int min, int max) {
  int x = getInt();
  while (x < min || x > max) {
    cout << "Invalid Selection, try again: ";
    x = getInt();
  }
  return x;
}

int validMemShip(int min, int max) {
  int val;
  int flag = 0;
  do {
    cin >> val;
    if (cin.fail()) {
      cout << "Invalid membership number, try again: ";
      cin.clear();
      while (cin.get() != '\n')
        ;
    } else if (cin.get() != '\n') {
      cout << "Invalid membership number, try again: ";
      while (cin.get() != '\n')
        ;
    } else if (val < min || val > max) {
      cout << "Invalid membership number, try again: ";
    } else
      flag = 1;

  } while (flag == 0);
  return val;
}

} // namespace sdds