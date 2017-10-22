#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main(int argv, char** argc) {
  if (argv != 2) {
    cout << "Please enter input filename." << endl;
    return 0;
  }

  string file = argc[1];
  if (file.substr(file.length() - 4) != ".asm") {
    cout << "Invalid file. File does not end in '.asm'." << endl;
    return 0;
  }
  ifstream inFile;

  inFile.open(file);
  if (!inFile) {
    cout << "File could not be read or found." << endl;
    return 0;
  }

  return 0;
}


