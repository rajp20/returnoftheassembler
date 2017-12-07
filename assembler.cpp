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
void addCodeToCOE(string linesToAdd, string out_file);
string getBinaryRegDecLabel(string arg, map<string, int> labelMap, int currentIndex);
void createColorPallet();

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
  
  regMapToBinary["$read_data"] = "10101";
  
  regMapToBinary["$x"] = "10110";
  regMapToBinary["$y"] = "10111";
  regMapToBinary["$data_ready"] = "11000";
  regMapToBinary["$left_click"] = "11001";
  regMapToBinary["$right_click"] = "11010";

  // All of the registers with their associated binary value. $lr0-$lr3
  regMapToBinary["$lr0"] = "11100";
  regMapToBinary["$lr1"] = "11101";
  regMapToBinary["$lr2"] = "11110";
  regMapToBinary["$lr3"] = "11111";

  createColorPallet();
 
  map<string, int> labelMap;
  labelMap["start"] = 6;
  firstPass(input_file, labelMap);
  secondPass(input_file, labelMap);
  return 0;
}

void createColorPallet() {
  ofstream newTextFile("text_glyph_code.coe", ios_base::app);

  ofstream newFile;
  newFile.open ("text_glyph_code.coe");
  // Make sure the file is readable.
  newFile << "memory_initialization_radix=2;\nmemory_initialization_vector=\n\n";
  int colorCount = 0;
  for (int row = 0; row < 240; row++) {
	int modded_row = row % 20;
	if (modded_row < 2 || (modded_row >= 18 && modded_row < 20)) {
	  for (int col = 0; col < 80; col++) {
		if (col == 5 && modded_row == 19) {
		  colorCount++;
		}
		if (col < 5 && colorCount == 0) {
		  newFile << "0010001000100010,\n";
		}
		else if (col < 5) {
		  newFile << "0001000100010001,\n";
		}
		else {
		  newFile << "0000000000000000,\n";
		}
	  }  
	}
	else if (modded_row >= 2 && modded_row < 18) {
	  for (int col = 0; col < 80; col++) {
		if (colorCount == 0) {
		  if (col == 0) {
			newFile << "0010001000000000,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "0000000000000000,\n";
		  }
		  else if (col == 4) {
			newFile << "0000000000100010,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 1) { // 3
		  if (col == 0) {
			newFile << "0001000100110011,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "0011001100110011,\n";
		  }
		  else if (col == 4) {
			newFile << "0011001100010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 2) { // 4
		  if (col == 0) {
			newFile << "0001000101000100,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "0100010001000100,\n";
		  }
		  else if (col == 4) {
			newFile << "0100010000010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 3) { // 5
		  if (col == 0) {
			newFile << "0001000101010101,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "0101010101010101,\n";
		  }
		  else if (col == 4) {
			newFile << "0101010100010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 4) { // 6
		  if (col == 0) {
			newFile << "0001000101100110,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "0110011001100110,\n";
		  }
		  else if (col == 4) {
			newFile << "0110011000010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 5) { // 7
		  if (col == 0) {
			newFile << "0001000101110111,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "0111011101110111,\n";
		  }
		  else if (col == 4) {
			newFile << "0111011100010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 6) { // 8
		  if (col == 0) {
			newFile << "0001000110001000,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "1000100010001000,\n";
		  }
		  else if (col == 4) {
			newFile << "1000100000010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 7) { // 9
		  if (col == 0) {
			newFile << "0001000110011001,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "1001100110011001,\n";
		  }
		  else if (col == 4) {
			newFile << "1001100100010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 8) { // 10
		  if (col == 0) {
			newFile << "0001000110101010,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "1010101010101010,\n";
		  }
		  else if (col == 4) {
			newFile << "1010101000010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 9) { // 11
		  if (col == 0) {
			newFile << "0001000110111011,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "1011101110111011,\n";
		  }
		  else if (col == 4) {
			newFile << "1011101100010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 10) { // 12
		  if (col == 0) {
			newFile << "0001000111001100,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "1100110011001100,\n";
		  }
		  else if (col == 4) {
			newFile << "1100110000010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
		else if (colorCount == 11) { // 13
		  if (col == 0) {
			newFile << "0001000111011101,\n";
		  }
		  else if (col > 0 && col < 4) {
			newFile << "1101110111011101,\n";
		  }
		  else if (col == 4) {
			newFile << "1101110100010001,\n";
		  }
		  else {
			newFile << "0000000000000000,\n";
		  }
		}
	  }	  
	}
	else {
	  for (int col = 0; col < 80; col++) {
		if (col < 5) {
		  newFile << "0001000100010001,\n";
		}
		else {
		  newFile << "0000000000000000,\n";
		}
	  }  
	}
  }

  newFile << "0000000011111111,\n"; // Canvas Color
  newFile << "0000000010110101,\n"; // Default color border
  newFile << "0000000010101010,\n"; // Current Slected color border
  newFile << "0000000011111111,\n"; // 3
  newFile << "0000000000000000,\n"; // 4
  newFile << "0000000011000000,\n"; // 5
  newFile << "0000000010010010,\n"; // 6
  newFile << "0000000011010101,\n"; // 7
  newFile << "0000000011000111,\n"; // 8
  newFile << "0000000000011011,\n"; // 9
  newFile << "0000000001001101,\n"; // 10
  newFile << "0000000001011110,\n"; // 11
  newFile << "0000000000111111,\n"; // 12
  newFile << "0000000011111011,\n"; // 13
  newFile << "0000000000111000,\n";
  newFile << "0000000010100011,\n"; // Cursor color
						  
  newFile.close();

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

  // // Output file

  string output = "";

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

        // Get the op code binary string.
        binaryCode += opCodeMapToBinary[tokens[0]];

        // Get the binary string of reg/decimal/lable.
        string firstArg = getBinaryRegDecLabel(tokens[1], labelMap, index + 1);

        // Only set the top bit if it's an immediate.
        if (firstArg.length() < 6) {
          binaryCode += "0";
        }
        binaryCode += firstArg;

        if (tokens.size() > 2) {
          binaryCode += getBinaryRegDecLabel(tokens[2], labelMap, index + 1);
        }
	binaryCode += ",\n";
	output += binaryCode;
        index++;
      }
    }
    string out_file = input_file.substr(0, input_file.size() - 4) + ".coe";
    addCodeToCOE(output, out_file);
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
    if (value >= -32 && value <= 31) {
      return bitset<6>(value).to_string();
    } else {
      cout << "Immediate value needs to be greater than -32 and less than 31, this will cause error in the core" << endl;
      return "1";
    }
  }

}

/*
 * Helper function. Adds one line to the output coe file.
 */
void addCodeToCOE(string linesToAdd, string out_file) {

  // Copy master coe to new file
  ifstream src("text_glyph_code.coe", ios::binary);
  ofstream dst(out_file, ios::binary);
  dst << src.rdbuf();
  src.close();
  dst.close();
  
  ofstream outFile;
  outFile.open(out_file, ios::app);
  linesToAdd[linesToAdd.length() - 2] = ';';
  outFile << linesToAdd;
  outFile.close();
}
