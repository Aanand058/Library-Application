
#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>
namespace sdds {

// String Copy
void strCpy(char *des, const char *src);

// String length
int strLen(const char *s);

int getInt();
int getIntRange(int, int);

int validMemShip(int min, int max);

} // namespace sdds
#endif // !