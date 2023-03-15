#include <fstream>

#include <iostream>

#include <sstream>

#include <string>

#include <vector>

#include <algorithm>

using namespace std;

int main() {
  ifstream file("program.cpp");

  if (file.is_open()) {
    string line;

    bool insideTheMainFunction = false;
    vector < string > variables;

    int variableCount = 0;
    int preprocessor1Count = 0;
    int preprocessor2Count = 0;
    vector < string > preprocessors;
    while (getline(file, line)) {
      if (line.find("int main()") != string::npos) {
        insideTheMainFunction = true;
        continue;
      }
      string newString = "";
      if (insideTheMainFunction) {
        if (line.find("int") != string::npos) {
          bool equalFound = false;
          bool commaFound = false;
          for (char & c: line) {
            if (equalFound) {
              newString = "";
              if (c == ',') {
                equalFound = false;
              }
              continue;
            }
            if (c == '=') {
              variableCount += 1;
              variables.push_back(newString);
              equalFound = true;
              newString = "";
            }
            if (c == ',') {
              variables.push_back(newString);
              variableCount += 1;
              commaFound = true;
              newString = "";
            }
            if (commaFound) {

              if (c != ';') {
                newString = "";
              }
              if (c == ';') {
                variableCount += 1;
                variables.push_back(newString);
                commaFound = false;
              }

            }
            newString += c;
            if (newString == "int" || newString == " ") {
              newString = "";
            }
          }
        }
        if (line.find("return 0") != string::npos) {
          break;
        }
      }

      string newString2 = "";
      bool hashFound = false;

      for (char & c: line) {
        if (c == '#') {
          hashFound = true;
          continue;
        }
        if (hashFound) {

          if (c == ' ' || c == '<') {
            preprocessors.push_back(newString2);
            hashFound = false;
            break;
          }
        }
        newString2 += c;

      }
    }

    for (int i = 0; i < variables.size(); i++) {
      std::cout << "Variable-" << i + 1 << ": " << variables.at(i) << endl;
    }

    cout << "Total number of the variables:" << variableCount << endl;

    sort(preprocessors.begin(), preprocessors.end());
    std::vector < std::string > unique_vector;
    for (auto element: preprocessors) {
      if (std::find(unique_vector.begin(), unique_vector.end(), element) == unique_vector.end()) {
        unique_vector.push_back(element);
      }
    }
    for (int j = unique_vector.size() - 1; j >= 0; j--) {
      std::cout << "Preprocessor-" << j + 1 << ": " << unique_vector.at(j) << endl;
    }
    cout << "Total number of preprocessor:" << unique_vector.size() << endl;
    file.close();

  } else {
    cerr << "Unable to open file!" << endl;
  }

  return 0;
}
