

#include "LibApp.h"
#include "Utils.h"
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;
namespace sdds {

bool LibApp::confirm(const char *message) {
  Menu m(message);
  m << "Yes";
  return m.run() == 1;
}

void LibApp::load() {
  
  ifstream fileRead(m_fileName);
  char type{};

  for (int i = 0; fileRead && i < SDDS_LIBRARY_CAPACITY; i++) {
    fileRead >> type;
    fileRead.ignore();

    if (fileRead) {
      if (type == 'P')
        m_ppa[i] = new Publication;

      else if (type == 'B')
        m_ppa[i] = new Book;

      if (m_ppa[i]) {

        fileRead >> *m_ppa[i];
        m_nolp++;

        m_llrn = m_ppa[i]->getRef();
      }
    }
  }
}

void LibApp::save() {
  cout << "Saving Data" << endl;
  ofstream outputFile(m_fileName);
  for (int i = 0; i < m_nolp; i++) {
    if (m_ppa[i]->getRef() != 0) {
      outputFile << *m_ppa[i] << endl;
    }
  }
  outputFile.close();
}

int LibApp::search(int search) {
  char searchTitle[256];
  int refNo = 0;

  PublicationSelector ps("Select one of the following found matches:");

  int type = m_pubType.run();
  char pubType = 'x';

  switch (type) {
  case 1:
    pubType = 'B';
    break;
  case 2:
    pubType = 'P';
    break;
  case 0:
    break;
  }
  if (type) {
    cout << "Publication Title: ";
    cin.getline(searchTitle, 256, '\n');
    for (int i = 0; i < m_nolp; i++) {
      if (m_ppa[i]->getRef() && m_ppa[i]->type() == pubType) {
        switch (search) {
        case 1:
          if (strstr(*m_ppa[i], searchTitle))
            ps << m_ppa[i];
          break;
        case 2:
          if (m_ppa[i]->onLoan() && strstr(*m_ppa[i], searchTitle))
            ps << m_ppa[i];

          break;
        case 3:
          if (!m_ppa[i]->onLoan() && strstr(*m_ppa[i], searchTitle))
            ps << m_ppa[i];
          break;
        }
      }
    }
    if (ps) {
      ps.sort();
      int ref = ps.run();
      if (ref) {
        refNo = ref;
        for (int i = 0; i < m_nolp; i++) {
          if (ref == m_ppa[i]->getRef()) {
            cout << *m_ppa[i] << endl;
            i = m_nolp;
          }
        }
      } else {
        cout << "Aborted!\n";
      }
    } else {
      cout << "No matches found!\n";
    }
  } else {
    cout << "Aborted!\n";
  }
  return refNo;
}

void LibApp::returnPub() {
  cout << "Return publication to the library" << endl;
  int ref = search(2);
  if (ref) {
    Publication *selected = getPub(ref);
    if (confirm("Return Publication?")) {
      int dateDiff = Date() - selected->checkoutDate();
      cout << setprecision(2) << fixed;
      if (dateDiff > 15) {
        cout << "Please pay $" << (dateDiff - 15) * 0.5 << " penalty for being "
             << dateDiff - 15 << " days late!" << endl;
      }
      selected->set(0);
      m_changed = true;
      cout << "Publication returned" << endl;
    }
  }
}

void LibApp::newPublication() {

  if (m_nolp == SDDS_LIBRARY_CAPACITY) {
    cout << "Library is at its maximum capacity!" << endl;
  } else {
    cout << "Adding new publication to the library" << endl;
    int select = m_pubType.run();
    if (select == 1 || select == 2) {
      Publication *pptr;
      if (select == 1) {
        pptr = new Book();
      } else {
        pptr = new Publication();
      }
      if (!(pptr->read(cin))) {
        cin.ignore(1000, '\n');
        cout << "Aborted!" << endl;
      } else {
        if (confirm("Add this publication to the library?")) {
          if (*pptr) {
            pptr->setRef(++m_llrn);
            m_ppa[m_nolp++] = pptr;
            m_changed = true;
            cout << "Publication added" << endl;
          } else {
            cout << "Failed to add publication!" << endl;
            delete pptr;
          }
        } else {
          cout << "Aborted!" << endl;
          delete pptr;
        }
      }

    } else {
      cout << "Aborted!" << endl;
    }
  }
}

void LibApp::removePublication() {
  cout << "Removing publication from the library" << endl;
  int libRef = search(1);
  if (libRef) {
    if (confirm("Remove this publication from the library?")) {
      getPub(libRef)->setRef(0);
      m_changed = true;
      cout << "Publication removed" << endl;
    }
  }
}

void LibApp::checkOutPub() {
  cout << "Checkout publication from the library" << endl;
  int ref = search(3);
  if (ref) {

    if (confirm("Check out publication?")) {
      cout << "Enter Membership number: ";
      int membership = validMemShip(10000, 99999);
      Publication *selectedpub = getPub(ref);
      selectedpub->set(membership);
      m_changed = true;
      cout << "Publication checked out" << endl;
    }
  }
}

void LibApp::run() {
  bool flag = true;

  int selection = -1;

  while (flag) {
    selection = m_mainMenu.run();
    if (selection == 1)
      newPublication();
    else if (selection == 2)
      removePublication();
    else if (selection == 3)
      checkOutPub();
    else if (selection == 4)
      returnPub();
    else {
      if (m_changed) {
        selection = m_exitMenu.run();
        if (selection == 1) {
          save();
          flag = false;
        } else if (selection == 0) {
          if (confirm("This will discard all the changes are you sure?")) {
            flag = false;
          }
        }
      } else
        flag = false;
    }
    cout << endl;
  }
  cout << "------------------------------------" << endl;
  cout << "Thanks for using Library Application" << endl <<endl;
}

Publication *LibApp::getPub(int libRef) {
  Publication *address = nullptr;
  for (int i = 0; i < m_nolp && !address; i++) {
    if (m_ppa[i]->getRef() == libRef)
      address = m_ppa[i];
  }
  return address;
}

LibApp::LibApp(const char *filename)
    : m_mainMenu("Library Application"),
      m_exitMenu(
          "Changes have been made to the data, what would you like to do?"),
      m_pubType("Choose the type of publication:") {

  if (filename) {
    strCpy(m_fileName, filename);
  }

  m_mainMenu << "Add New Publication"
             << "Remove Publication"
             << "Checkout publication from library"
             << "Return publication to library";

  m_exitMenu << "Save changes and exit"
             << "Cancel and go back to the main menu";

  m_pubType << "Book"
            << "Publication";

  load();
}

LibApp::~LibApp() {
  for (int i = 0; i < m_nolp; i++) {
    delete m_ppa[i];
  }
}

} // namespace sdds
