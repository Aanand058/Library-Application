#include "Date.h"
#include "LibApp.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

struct Lib {
  char B_P = 'x';
  int libRef;
  char shelfId[20];
  char tempTitle[256];
  int memshipId;
  sdds::Date tempDate;
  char authName[256];
};

void displayHeader();
void displayData(const Lib &data);

void readData(const char *filename) {
  std::ifstream inFile(filename);

  Lib data;
  displayHeader();

  while (inFile) {
    inFile >> data.B_P;
    inFile.ignore();

    inFile >> data.libRef;
    inFile.ignore();

    inFile >> data.shelfId;
    inFile.ignore();

    inFile.getline(data.tempTitle, 255, '\t');

    inFile >> data.memshipId;
    inFile.ignore();

    inFile >> data.tempDate;

    inFile.getline(data.authName, 255, '\n');

    displayData(data);
    
  }
}

void displayHeader() {
  cout << "B/P | LibRef |LocID | Title                                   |Mem ID | Date       "
          "| Author          |"
       << endl
       << "-----+--------+------+-----------------------------------------+-------+------------+"
          "-----------------|"
       << endl;

}

void displayData( const Lib &data) {
  
cout << data.B_P <<"    " << "  "<<data.libRef;
  cout << "    "<< data.shelfId <<"   ";

  cout.width(40);
  cout.setf(ios::left);
  cout<< data.tempTitle;
  cout.unsetf(ios::left);
  

  if(data.memshipId !=0){
  cout << "  " << data.memshipId;}
  else{
    cout.width(5);
    cout.setf(ios::left);
  cout<< "  N/A  ";
  cout.unsetf(ios::left);
  }
  
  cout <<"   " <<data.tempDate;
  cout<< data.authName; 
  cout << endl;
   
  
}

int main() {

  // setting date values
  sdds::sdds_day = 10;
  sdds::sdds_mon = 8;
  sdds::sdds_year = 2023;
  sdds::sdds_test = true;

  sdds::LibApp theApp("Content.txt");
  theApp.run();


  //Printing Data of the file
  cout << "Content of the File" << endl;
  readData("Content.txt");
  

  return 0;
}