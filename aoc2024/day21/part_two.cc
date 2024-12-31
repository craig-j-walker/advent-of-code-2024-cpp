
module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <tuple>
#include <utility>
#include <vector>

export module part_two;

using namespace std;

export namespace part_two {

void ParseInput(const string_view Input, vector<string> &Codes) {
  stringstream ss((string(Input)));
  string code{};

  while (getline(ss, code, '\n')) {
    Codes.push_back(code);
  }
}

class DirPad {

  /*     +---+---+
      | ^ | A |
  +---+---+---+
  | < | v | > |
  +---+---+---+ */

  const vector<vector<string>> m_translation{
      // 0 = ^
      // 1 = v
      // 2 = <
      // 3 = >
      // 4 = A
      {"A", "vA", "v<A", "v>A,>vA", ">A"},
      {"^A", "A", "<A", ">A", "^>A,>^A"},
      {">^A", ">A", "A", ">>A", ">>^A"},
      {"^<A,<^A", "<A", "<<A", "A", "^A"},
      {"<A", "v<A,<vA", "v<<A", "vA", "A"}};

  void TranslateButton(char &Button) {
    switch (Button) {
    case '^':
      Button = 0;
      break;
    case 'v':
      Button = 1;
      break;
    case '<':
      Button = 2;
      break;
    case '>':
      Button = 3;
      break;
    case 'A':
      Button = 4;
      break;
    default:
      throw exception();
      break;
    }
  }

public:
  uint64_t PushButton(char Button, char NextButton, int Level,
                      map<tuple<char, char, int>, uint64_t> &PushButtonMap,
                      int Depth) {
    TranslateButton(Button);
    TranslateButton(NextButton);
    tuple<char, char, int> key{Button, NextButton, Level};
    if (!PushButtonMap.contains(key)) {
      string codeString = m_translation[Button][NextButton];
      istringstream ss(codeString);
      string code;
      uint64_t codeLength = UINT64_MAX;
      vector<string> codePaths;
      if (Level == Depth) {
        while (getline(ss, code, ',')) {
          if (code.length() < codeLength) {
            codeLength = code.length();
          }
        }
        PushButtonMap.insert(make_pair(key, codeLength));
      } else {
        while (getline(ss, code, ',')) {
          uint64_t newCodeLength = 0;
          Button = 'A';
          for (int i = 0; i < code.length(); i++) {
            newCodeLength +=
                PushButton(Button, code[i], Level + 1, PushButtonMap, Depth);
            Button = code[i];
          }
          if (newCodeLength < codeLength) {
            codeLength = newCodeLength;
          }
        }
        PushButtonMap.insert(make_pair(key, codeLength));
      }
    }
    return PushButtonMap.find(key)->second;
  }
};

class NumPad {
  /* +---+---+---+
  | 7 | 8 | 9 |
  +---+---+---+
  | 4 | 5 | 6 |
  +---+---+---+
  | 1 | 2 | 3 |
  +---+---+---+
      | 0 | A |
      +---+---+ */

  const vector<vector<string>> m_translation{
      {"A", "^<A", "^A", "^>A,>^A", "^^<A", "^^A", "^^>A,>^^A", "^^^<A", "^^^A",
       "^^^>,>^^^A", ">A"},
      {">vA", "A", ">A", ">>A", "^A", "^>A,>^A", "^>>A,>>^A", "^^A",
       "^^>A,>^^A", "^^>>A,>>^^A", ">>vA"},
      {"vA", "<A", "A", ">A", "^<A,<^A", "^A", "^>A,>^A", "^^<A,<^^A", "^^A",
       "^^>A,>^^A", "v>A,>vA"},
      {"v<A,<vA", "<<A", "<A", "A", "^<<A,<<^A", "^<A,<^A", "^A", "^^<<A,<<^^A",
       "^^<A,<^^A", "^^A", "vA"},
      {">vvA", "vA", "v>A,>vA", "v>>A,>>vA", "A", ">A", ">>A", "^A", "^>A,>^A",
       "^>>A,>>^A", ">>vvA"},
      {"vvA", "v<A,<vA", "vA", "v>A,>vA", "<A", "A", ">A", "^<A,<^A", "^A",
       "^>A,>^A", "vv>A,>vvA"},
      {"vv<A,<vvA", "v<<A,<<vA", "v<A,<vA", "vA", "<<A", "<A", "A", "^<<A,<<^A",
       "^<A,<^A", "^A", "vvA"},
      {">vvA", "vvA", "vv>A,>vvA", "vv>>A,>>vvA", "vA", "v>A,>vA", "v>>A,>>vA",
       "A", ">A", ">>A", ">>vvvA"},
      {"vvvA", "vv<A,<vvA", "vvA", "vv>A,>vvA", "v<A,<vA", "vA", "v>A,>vA",
       "<A", "A", ">A", "vvv>A,>vvvA"},
      {"vvv<A,<vvvA", "vv<<A,<<vvA", "vv<A,<vvA", "vvA", "v<<A,<<vA", "v<A,<vA",
       "vA", "<<A", "<A", "A", "vvvA"},
      {"<A", "^<<A", "^<A,<^A", "^A", "^^<<A", "^^<A,<^^A", "^^A", "^^^<<A",
       "^^^<A,<^^^A", "^^^A", "A"}};

  int m_dirPads;
  DirPad m_dirPad;

  void TranslateButton(char &Button) {
    switch (Button) {
    case '0':
      Button = 0;
      break;
    case '1':
      Button = 1;
      break;
    case '2':
      Button = 2;
      break;
    case '3':
      Button = 3;
      break;
    case '4':
      Button = 4;
      break;
    case '5':
      Button = 5;
      break;
    case '6':
      Button = 6;
      break;
    case '7':
      Button = 7;
      break;
    case '8':
      Button = 8;
      break;
    case '9':
      Button = 9;
      break;
    case 'A':
      Button = 10;
      break;
    default:
      throw exception();
      break;
    }
  }

  uint64_t
  DirPadCodePath(string Code, int Level,
                 map<tuple<char, char, int>, uint64_t> &PushButtonMap) {
    char Button;
    uint64_t codeLength;
    Button = 'A';
    codeLength = 0;
    for (int i = 0; i < Code.length(); i++) {

      codeLength +=
          m_dirPad.PushButton(Button, Code[i], Level, PushButtonMap, m_dirPads);
      Button = Code[i];
    }
    return codeLength;
  }

public:
  NumPad(int dirPads) { m_dirPads = dirPads; }

  uint64_t PushButton(char Button, char NextButton,
                      map<tuple<char, char, int>, uint64_t> &PushButtonMap) {

    TranslateButton(Button);
    TranslateButton(NextButton);
    string codeString = m_translation[Button][NextButton];
    istringstream ss(codeString);
    string code;
    vector<tuple<string, char, int>> paths;
    vector<string> tempCodePaths2;
    vector<string> tempCodePaths;
    vector<string> codePaths;
    uint64_t codeLength = 0;
    uint64_t minCodeLength = UINT64_MAX;
    while (getline(ss, code, ',')) {

      codeLength = DirPadCodePath(code, 1, PushButtonMap);
      if (codeLength < minCodeLength) {
        minCodeLength = codeLength;
      }
    }

    return minCodeLength;
  }
};

uint64_t result(const string_view input) {

  vector<string> codes;
  uint64_t totalComplexity = 0;
  ParseInput(input, codes);
  map<tuple<char, char, int>, uint64_t> pushButtonMap;

  for (auto &code : codes) {
    NumPad numPad{25};
    cout << "code: " << code << endl;
    char Button = 'A';
    uint64_t minTotalLength = 0;
    uint64_t complexity = 0;
    for (int i = 0; i < code.length(); i++) {
      cout << "transition to " << code.at(i) << ":" << endl;
      uint64_t path = numPad.PushButton(Button, code[i], pushButtonMap);
      minTotalLength += path;
      Button = code[i];
    }
    cout << "Min Total Length = " << minTotalLength << endl;
    complexity = minTotalLength * stoll(code.substr(0, 3));
    totalComplexity += complexity;
  }

  return totalComplexity;
}
} // namespace part_two