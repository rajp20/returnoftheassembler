#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void firstRead(string fileName);
void secondRead(string fileName);
void saveToCOE(string fileName);
void add_register_value(string reg, string ins);

// All of the binary opcodes associated with their instruction.
const ADD_OP = "00000";
const SUB_OP = "00001";
const ADDI_OP = "00010";
const SLLI_OP = "00011";
const SLRI_OP = "00100";
const JUMP_OP = "00101";
const JUMPLI_OP = "00110";
const JUMPL_OP = "00111";
const JUMPG_OP = "01000";
const JUMPE_OP = "01001";
const JUMPNE_OP = "01010";
const CMP_OP = "01011";
const RET_OP = "01100";
const LOAD_OP = "01101";
const LOADI_OP = "01110";
const STORE_OP = "01111";
const MOV_OP = "10000";

// All of the registers with their associated binary value. $r0 - $r27



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

  // Make sure the file is readable.
  inFile.open(file);
  if (!inFile) {
    cout << "File could not be read or found." << endl;
    return 0;
  }

  // Open the COE file that the data is being written to.
  ofstream outputFile("./ram_data.coe");

  string current_token;
  string next_token;

  // keep reading in data if there is still data to be read
  while (infile >> current_token)
  {
    switch (current_token) {
      case "add":

      break;

      case "sub":

      break;

      case "addi":

      break;

      case "shlli":

      break;

      case "shrli":

      break;

      case "jump":

      break;

      case "jumpli":

      break;

      case "jumpl":

      break;

      case "jumpg":

      break;

      case "jumpe":

      break;

      case "jumpne":

      break;

      case "cmp":

      break;

      case "ret":

      break;

      case "load":

      break;

      case "loadi":

      break;

      case "store":

      break;

      case "mov":

      break;


    }
  }

  outputFile.close();
  inFile.close();

  return 0;
}

void add_register_value(string reg, string ins){


}
