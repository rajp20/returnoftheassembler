#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

void firstPass(string input_file, map<string, int>& labelMap);
bool isLabel(string line);
void secondPass(string input_file, map<string, int> labelMap);
void addLineToCOE(ofstream& out_file, string lineToAdd);
string getBinaryOfAssemblyIns(string assemblyInstruction);
string getBinaryOfRegisterOrHex(string arg, map<string, int> labelMap);


string add_register_value(string reg, string ins);

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

  string input_file = argc[1];
  if (input_file.substr(input_file.length() - 4) != ".asm") {
    cout << "Invalid file. File does not end in '.asm'." << endl;
    return 0;
  }

  ifstream inFile;
  // Make sure the file is readable.
  inFile.open(input_file);
  if (!inFile) {
    cout << "File could not be read or found." << endl;
    return 0;
  }
  inFile.close();

  map<string, int> labelMap;
  firstPass(input_file, labelMap);
  secondPass(input_file, labelMap);

  return 0;
}

/*
 * Used as the first pass through. Leave labels in jump functions as the label,
 * but record the address of the label when you pass through it so you can
 * change it in the second passthrough.
 */
void firstPass(string input_file, map<string, int>& labelMap)
{
  string line;
  int index;
  ifstream inFile;
  inFile.open(input_file);
  if (inFile.is_open()) {
    while (getline(inFile, line)) {
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      if (isLabel(line)) {
        // Remove the last char in the string
        string label = line.substr(0, line.size() - 1);
        labelMap[label] = index;
      } else {
        index++;
      }
    }
    inFile.close();
  }
}

/*
 * Helper function which returns true if the input string is a label.
 * False otherwise.
 */
bool isLabel(string line) {
  char endOfLine = line[line.length() - 1];
  return endOfLine == ':';
}

/*
 * Generates output binary string.
 */
void secondPass(string input_file, map<string, int> labelMap) {
  string line;
  int index;

  // Input file
  ifstream inFile;
  inFile.open(input_file);

  // Output file
  string out_file = input_file.substr(0, line.size() - 4) + ".coe";
  ofstream outFile(out_file);

  if (inFile.is_open()) {
    while (getine(inFile, line)) {
      line.erase(remove(line.begin(), line.end(), '\t'), line.end());
      if (!isLabel(line)) {
        string binaryCode;
        vector<string> tokens;
        split(tokens, line, is_any_of(" "));
        binaryCode += getBinaryOfOpCode(tokens[0]);
        binaryCode += getBinaryOfOp(token[1]);
        if (vector.size() > 2) {
          binaryCode += getBinaryOfOp(token[2]);
        }
        addLineToCOE(outFile, binaryCode);
      }
    }
    if (outFile.is_open()) {
      outFile.close();
    }
    inFile.close();
  }
}

/*
 * Returns the binary opCODE for the associated assembly instruction
 */
string getBinaryOfAssemblyIns(string assemblyInstruction) {
  switch (assemblyInstruction) {
    case "add":
      return ADD_OP;
    break;

    case "sub":
      return SUB_OP;
    break;

    case "addi":
      return ADDI_OP;
    break;

    case "shlli":
      return SHLLI_OP;
    break;

    case "shrli":
      return SHRLI_OP;
    break;

    case "jump":
      return JUMP_OP;
    break;

    case "jumpli":
      return JUMPLI_OP;
    break;

    case "jumpl":
      return JUMPL_OP;
    break;

    case "jumpg":
      return JUMPG_OP;
    break;

    case "jumpe":
      return JUMPE_OP;
    break;

    case "jumpne":
      return JUMPNE_OP;
    break;

    case "cmp":
      return CMP_OP;
    break;

    case "ret":
      return RET_OP;
    break;

    case "load":
      return LOAD_OP;
    break;

    case "loadi":
      return LOADI_OP;
    break;

    case "store":
      return STORE_OP;
    break;

    case "mov":
      return MOV_OP;
    break;

    default:
      std::cout << "Error: Recieved wrong opcode. " <<  opCode << " is not a registered OPCODE." << '\n';
      return NULL;
    break;
  }
}

/*
 * Returns the binary of the operands.
 */
string getBinaryOfRegisterOrHex(string arg, map<string, int> labelMap) {

  // If the first character of the string is a $, then we know that this string is a register.
  if (arg[0] == '$') {
    switch (arg)
    {
      case "$r0":
        return R0_VALUE;
      break;

      case "$r1":
        return R1_VALUE;
      break;

      case "$r2":
        return R2_VALUE;
      break;

      case "$r3":
        return R3_VALUE;
      break;

      case "$r4":
        return R4_VALUE;
      break;

      case "$r5":
        return R5_VALUE;
      break;

      case "$r6":
        return R6_VALUE;
      break;

      case "$r7":
        return R7_VALUE;
      break;

      case "$r8":
        return R8_VALUE;
      break;

      case "$r9":
        return R9_VALUE;
      break;

      case "$r10":
        return R10_VALUE;
      break;

      case "$r11":
        return R11_VALUE;
      break;

      case "$r12":
        return R12_VALUE;
      break;

      case "$r13":
        return R13_VALUE;
      break;

      case "$r14":
        return R14_VALUE;
      break;

      case "$r15":
        return R15_VALUE;
      break;

      case "$r16":
        return R16_VALUE;
      break;

      case "$r17":
        return R17_VALUE;
      break;

      case "$r18":
        return R18_VALUE;
      break;

      case "$r19":
        return R19_VALUE;
      break;

      case "$r20":
        return R20_VALUE;
      break;

      case "$r21":
        return R21_VALUE;
      break;

      case "$r22":
        return R22_VALUE;
      break;

      case "$r23":
        return R23_VALUE;
      break;

      case "$r24":
        return R24_VALUE;
      break;

      case "$r25":
        return R25_VALUE;
      break;

      case "$r26":
        return R26_VALUE;
      break;

      case "$r27":
        return R27_VALUE;
      break;

      case "$lr0":
        return LR0_VALUE;
      break;

      case "$lr1":
        return LR1_VALUE;
      break;

      case "$lr2":
        return LR2_VALUE;
      break;

      case "$lr3":
        return LR3_VALUE;
      break;

      default:
        std::cout << "Incorrect register name. " <<  reg << " is not a register name." << '\n';
        return NULL;
      break;
    }
  }
  // If the string starts with 0x then we know that this is a hexidecimal value that needs to be
  // converted to binary.
  else  if (arg[0] == '0' && arg[1] == 'x') {
    return get_binary_string_from_hex_string(arg);
  }
  // If this is not a hex value or register, then we know that it is a label
  else {
    return labelMap[arg];
  }
}

/*
 * Helper function. Adds one line to the output coe file.
 */
void addLineToCOE(ofstream& out_file, string lineToAdd) {
  if (out_file.is_open()) {
    out_file << lineToAdd << "\n";
  }
}


string get_binary_string_from_hex_string (string sHex)
{
  string sReturn = "";
  for (int i = 0; i < sHex.length (); ++i)
  {
    switch (sHex [i])
    {
      case '0': sReturn.append ("0000"); break;
      case '1': sReturn.append ("0001"); break;
      case '2': sReturn.append ("0010"); break;
      case '3': sReturn.append ("0011"); break;
      case '4': sReturn.append ("0100"); break;
      case '5': sReturn.append ("0101"); break;
      case '6': sReturn.append ("0110"); break;
      case '7': sReturn.append ("0111"); break;
      case '8': sReturn.append ("1000"); break;
      case '9': sReturn.append ("1001"); break;
      case 'a': sReturn.append ("1010"); break;
      case 'b': sReturn.append ("1011"); break;
      case 'c': sReturn.append ("1100"); break;
      case 'd': sReturn.append ("1101"); break;
      case 'e': sReturn.append ("1110"); break;
      case 'f': sReturn.append ("1111"); break;
    }
  }
  return sReturn;
}
