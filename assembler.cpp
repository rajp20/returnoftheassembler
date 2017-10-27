#include <fstream>
#include <string>
#include <map>
#include <bitset>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
using namespace std;

void firstPass(string input_file, map<string, int>& labelMap);
bool isLabel(string line);
void secondPass(string input_file, map<string, int> labelMap);
void addLineToCOE(ofstream& out_file, string lineToAdd);
string getBinaryRegDecLabel(string arg, map<string, int> labelMap, int currentIndex);

map<string, string> opCodeMapToBinary;
map<string, string> regMapToBinary;

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

  // All of the binary opcodes associated with their instruction.
  opCodeMapToBinary["add"]    = "00000";
  opCodeMapToBinary["sub"]    = "00001";
  opCodeMapToBinary["addi"]   = "00010";
  opCodeMapToBinary["shlli"]  = "00011";
  opCodeMapToBinary["shrli"]  = "00100";
  opCodeMapToBinary["jump"]   = "00101";
  opCodeMapToBinary["jumpli"] = "00110";
  opCodeMapToBinary["jumpl"]  = "00111";
  opCodeMapToBinary["jumpg"]  = "01000";
  opCodeMapToBinary["jumpe"]  = "01001";
  opCodeMapToBinary["jumpne"] = "01010";
  opCodeMapToBinary["cmp"]    = "01011";
  opCodeMapToBinary["ret"]    = "01100";
  opCodeMapToBinary["load"]   = "01101";
  opCodeMapToBinary["loadi"]  = "01110";
  opCodeMapToBinary["store"]  = "01111";
  opCodeMapToBinary["mov"]    = "10000";

  // All of the registers with their associated binary value. $r0 - $r27
  regMapToBinary["$r0"]  = "00000";
  regMapToBinary["$r1"]  = "00001";
  regMapToBinary["$r2"]  = "00010";
  regMapToBinary["$r3"]  = "00011";
  regMapToBinary["$r4"]  = "00100";
  regMapToBinary["$r5"]  = "00101";
  regMapToBinary["$r6"]  = "00110";
  regMapToBinary["$r7"]  = "00111";
  regMapToBinary["$r8"]  = "01000";
  regMapToBinary["$r9"]  = "01001";
  regMapToBinary["$r10"] = "01010";
  regMapToBinary["$r11"] = "01011";
  regMapToBinary["$r12"] = "01100";
  regMapToBinary["$r13"] = "01101";
  regMapToBinary["$r14"] = "01110";
  regMapToBinary["$r15"] = "01111";
  regMapToBinary["$r16"] = "10000";
  regMapToBinary["$r17"] = "10001";
  regMapToBinary["$r18"] = "10001";
  regMapToBinary["$r19"] = "10010";
  regMapToBinary["$r20"] = "10011";
  regMapToBinary["$r21"] = "10100";
  regMapToBinary["$r22"] = "10101";
  regMapToBinary["$r23"] = "10110";
  regMapToBinary["$r24"] = "10111";
  regMapToBinary["$r25"] = "11000";
  regMapToBinary["$r26"] = "11001";
  regMapToBinary["$r27"] = "11010";

  // All of the registers with their associated binary value. $lr0-$lr3
  regMapToBinary["$lr0"] = "11100";
  regMapToBinary["$lr1"] = "11101";
  regMapToBinary["$lr2"] = "11110";
  regMapToBinary["$lr3"] = "11111";

  map<string, int> labelMap;
  labelMap["start"] = 6;
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
  int index = 0;
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
  int index = 0;

  // Input file
  ifstream inFile;
  inFile.open(input_file);

  // Output file
  string out_file = input_file.substr(0, input_file.size() - 4) + ".coe";
  ofstream outFile(out_file);

  if (inFile.is_open()) {
    while (getline(inFile, line)) {
      line.erase(remove(line.begin(), line.end(), '\t'), line.end());
      line.erase(remove(line.begin(), line.end(), ','), line.end());
      if (!isLabel(line)) {
        // Split string in to tokens.
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end);

        string binaryCode;

        // This is temp until we figure out what we're going to use the
        // extra bit for since we're modifying our assembly language. 
        if (tokens.size() > 2) {
          binaryCode += "0";
        }

        // Get the op code binary string.
        binaryCode += opCodeMapToBinary[tokens[0]];

        // Get the binary string of reg/decimal/lable.
        binaryCode += getBinaryRegDecLabel(tokens[1], labelMap, index + 1);
        if (tokens.size() > 2) {
          binaryCode += getBinaryRegDecLabel(tokens[2], labelMap, index + 1);
        }
        addLineToCOE(outFile, binaryCode);
        index++;
      }
    }
    if (outFile.is_open()) {
      outFile.close();
    }
    inFile.close();
  }
}

/*
 * Returns the binary of the operands.
 */
string getBinaryRegDecLabel(string arg, map<string, int> labelMap, int currentIndex) {

  // If the first character of the string is a $, then we know that this string is a register.
  if (arg[0] == '$') {
    return regMapToBinary[arg];
  }
  // If the argument is in the label map, than arg is label.
  else  if (labelMap.count(arg)) {
    int labelIndex = labelMap[arg];
    int offset = labelIndex - currentIndex;
    return bitset<11>(offset).to_string();
  }
  // If the string is a decimal.
  else {
    int value = stoi(arg);
    if (!(value > 32)) {
      return bitset<5>(value).to_string();
    } else {
      cout << "Immediate value is more than 32, this will cause error in the core" << endl;
      return "1";
    }
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
