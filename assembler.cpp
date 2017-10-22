#include <fstream>
#include <iostream>
using namespace std;

int main(int argv, char** argc) {
  if (argv != 2) {
    cout << "Please enter input filename." << endl;
    return 0;
  }
  char* file = argc[1];
  ifstream inFile;

  inFile.open(file);
  if (!inFile) {
    cout << "File could not be read." << endl;
    return 0;
  }

  return 0;
}


