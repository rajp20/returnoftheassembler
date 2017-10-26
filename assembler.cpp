#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void firstRead(ifstream input_file, fstream output_file);
void secondRead(string fileName);
void saveToCOE(string fileName);
void add_register_value(string reg, string ins);

// All of the binary opcodes associated with their instruction.
const string ADD_OP = "00000";
const string SUB_OP = "00001";
const string ADDI_OP = "00010";
const string SHLLI_OP = "00011";
const string SHLRI_OP = "00100";
const string JUMP_OP = "00101";
const string JUMPLI_OP = "00110";
const string JUMPL_OP = "00111";
const string JUMPG_OP = "01000";
const string JUMPE_OP = "01001";
const string JUMPNE_OP = "01010";
const string CMP_OP = "01011";
const string RET_OP = "01100";
const string LOAD_OP = "01101";
const string LOADI_OP = "01110";
const string STORE_OP = "01111";
const string MOV_OP = "10000";

// All of the registers with their associated binary value. $r0 - $r27
const string R0_VALUE = "00000";
const string R1_VALUE = "00001";
const string R2_VALUE = "00010";
const string R3_VALUE = "00011";
const string R4_VALUE = "00100";
const string R5_VALUE = "00101";
const string R6_VALUE = "000110";
const string R7_VALUE = "00111";
const string R8_VALUE = "01000";
const string R9_VALUE = "01001";
const string R10_VALUE = "01010";
const string R11_VALUE = "01011";
const string R12_VALUE = "01100";
const string R13_VALUE = "01101";
const string R14_VALUE = "01110";
const string R15_VALUE = "01111";
const string R16_VALUE = "10000";
const string R17_VALUE = "10001";
const string R18_VALUE = "10010";
const string R19_VALUE = "10011";
const string R20_VALUE = "10100";
const string R21_VALUE = "10101";
const string R22_VALUE = "10110";
const string R23_VALUE = "10111";
const string R24_VALUE = "11000";
const string R25_VALUE = "11001";
const string R26_VALUE = "11010";
const string R27_VALUE = "11011";

// All of the registers with their associated binary value. $lr0-$lr3
const string LR0_VALUE = "11100";
const string LR1_VALUE = "11101";
const string LR2_VALUE = "11110";
const string LR3_VALUE = "11111";

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

  firstRead(inFile, outputFile);
  // secondRead();

  outputFile.close();
  inFile.close();

  return 0;
}

/*
  Used as the first pass through. Leave labels in jump functions as the label,
  but record the address of the label when you pass through it so you can
  change it in the second passthrough.
*/
void firstRead(ifstream input_file, fstream output_file)
{
  string current_instruction;
  string current_token;
  string next_token;

  // keep reading in data if there is still data to be read
  while (infile >> current_token)
  {
    switch (current_token) {
      case "add":
        current_instruction += ADD_OP;
      break;

      case "sub":
        current_instruction += SUB_OP;
      break;

      case "addi":
        current_instruction += ADDI_OP;
      break;

      case "shlli":
        current_instruction += SHLLI_OP;
      break;

      case "shrli":
        current_instruction += SHRLI_OP;
      break;

      case "jump":
        current_instruction += JUMP_OP;
      break;

      case "jumpli":
        current_instruction += JUMPLI_OP;
      break;

      case "jumpl":
        current_instruction += JUMPL_OP;
      break;

      case "jumpg":
        current_instruction += JUMPG_OP;
      break;

      case "jumpe":
        current_instruction += JUMPE_OP;
      break;

      case "jumpne":
        current_instruction += JUMPNE_OP;
      break;

      case "cmp":
        current_instruction += CMP_OP;
      break;

      case "ret":
        current_instruction += RET_OP;
      break;

      case "load":
        current_instruction += LOAD_OP;
      break;

      case "loadi":
        current_instruction += LOADI_OP;
      break;

      case "store":
        current_instruction += STORE_OP;
      break;

      case "mov":
        current_instruction += MOV_OP;
      break;

      default:

      break;
    }
    current_instruction = "";
  }
}

void add_register_value(string reg, string ins){
  switch (reg)
  {
    case "$r0":
      ins += R0_VALUE;
      return;
    break;

    case "$r1":
      ins += R1_VALUE;
      return;
    break;

    case "$r2":
      ins += R2_VALUE;
      return;
    break;

    case "$r3":
      ins += R3_VALUE;
      return;
    break;

    case "$r4":
      ins += R4_VALUE;
      return;
    break;

    case "$r5":
      ins += R5_VALUE;
      return;
    break;

    case "$r6":
      ins += R6_VALUE;
      return;
    break;

    case "$r7":
      ins += R7_VALUE;
      return;
    break;

    case "$r8":
      ins += R8_VALUE;
      return;
    break;

    case "$r9":
      ins += R9_VALUE;
      return;
    break;

    case "$r10":
      ins += R10_VALUE;
      return;
    break;

    case "$r11":
      ins += R11_VALUE;
      return;
    break;

    case "$r12":
      ins += R12_VALUE;
      return;
    break;

    case "$r13":
      ins += R13_VALUE;
      return;
    break;

    case "$r14":
      ins += R14_VALUE;
      return;
    break;

    case "$r15":
      ins += R15_VALUE;
      return;
    break;

    case "$r16":
      ins += R16_VALUE;
      return;
    break;

    case "$r17":
      ins += R17_VALUE;
      return;
    break;

    case "$r18":
      ins += R18_VALUE;
      return;
    break;

    case "$r19":
      ins += R19_VALUE;
      return;
    break;

    case "$r20":
      ins += R20_VALUE;
      return;
    break;

    case "$r21":
      ins += R21_VALUE;
      return;
    break;

    case "$r22":
      ins += R22_VALUE;
      return;
    break;

    case "$r23":
      ins += R23_VALUE;
      return;
    break;

    case "$r24":
      ins += R24_VALUE;
      return;
    break;

    case "$r25":
      ins += R25_VALUE;
      return;
    break;

    case "$r26":
      ins += R26_VALUE;
      return;
    break;

    case "$r27":
      ins += R27_VALUE;
      return;
    break;

    case "$lr0":
      ins += LR0_VALUE;
      return;
    break;

    case "$lr1":
      ins += LR1_VALUE;
      return;
    break;

    case "$lr2":
      ins += LR2_VALUE;
      return;
    break;

    case "$lr3":
      ins += LR3_VALUE;
      return;
    break;
  }
}
