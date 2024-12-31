
module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <tuple>
#include <vector>

export module part_one;

using namespace std;

export namespace part_one {

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
  vector<string> PushButton(char Button, char NextButton) {
    TranslateButton(Button);
    TranslateButton(NextButton);
    string codeString = m_translation[Button][NextButton];
    istringstream ss(codeString);
    string code;
    vector<string> codePaths;

    while (getline(ss, code, ',')) {
      codePaths.push_back(code);
    }
    return codePaths;
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

  vector<string> DirPadCodePath(vector<string> CodePaths) {
    char Button = 'A';
    int Position = 0;
    vector<string> codePaths;
    vector<tuple<string, char, int>> paths;
    for (auto const &code : CodePaths) {
      paths.push_back(make_tuple(code, Button, Position));
      while (!paths.empty()) {
        auto path = paths.back();
        paths.pop_back();
        auto pathString = get<0>(path);
        auto pathButton = get<1>(path);
        auto pathPos = get<2>(path);
        if (pathPos == pathString.length()) {
          codePaths.push_back(pathString);
        } else {
          for (auto const &dirPadPath :
               m_dirPad.PushButton(pathButton, pathString[pathPos])) {
            string tempString = pathString.substr(0, pathPos);
            tempString += dirPadPath;
            tempString += pathString.substr(pathPos + 1);
            paths.push_back(make_tuple(tempString, pathString[pathPos],
                                       pathPos + dirPadPath.length()));
          }
        }
      }
    }
    return codePaths;
  }

public:
  NumPad(int dirPads) { m_dirPads = dirPads; }

  vector<string> PushButton(char Button, char NextButton) {

    TranslateButton(Button);
    TranslateButton(NextButton);
    string codeString = m_translation[Button][NextButton];
    istringstream ss(codeString);
    string code;
    vector<tuple<string, char, int>> paths;
    vector<string> tempCodePaths2;
    vector<string> tempCodePaths;
    vector<string> codePaths;
    while (getline(ss, code, ',')) {
      tempCodePaths2.clear();
      tempCodePaths2.push_back(code);
      for (int i = 0; i < m_dirPads; i++) {
        for (auto const &path : DirPadCodePath(tempCodePaths2)) {
          tempCodePaths.push_back(path);
        }
        tempCodePaths2 = tempCodePaths;
        tempCodePaths.clear();
      }
      for (auto const &path : tempCodePaths2) {
        codePaths.push_back(path);
      }
    }
    return codePaths;
  }
};

uint64_t result(const string_view input) {

  vector<string> codes;
  uint64_t totalComplexity = 0;
  ParseInput(input, codes);

  for (auto &code : codes) {
    NumPad numPad{2};
    cout << "code: " << code << endl;
    char Button = 'A';
    uint64_t minTotalLength = 0;
    uint64_t complexity = 0;
    for (int i = 0; i < code.length(); i++) {
      uint64_t pathLength = UINT64_MAX;
      cout << "transition to " << code.at(i) << ":" << endl;
      int j = 0;
      for (auto const &path : numPad.PushButton(Button, code[i])) {

        if (path.length() < pathLength) {
          pathLength = path.length();
        }
        cout << "codePath " << j << ": " << path
             << ", length: " << path.length() << endl;
        j++;
      }
      cout << "Min Path Length = " << pathLength << endl;
      minTotalLength += pathLength;
      Button = code[i];
    }
    cout << "Min Total Length = " << minTotalLength << endl;
    complexity = minTotalLength * stoll(code.substr(0, 3));
    totalComplexity += complexity;
  }

  return totalComplexity;
}
} // namespace part_one