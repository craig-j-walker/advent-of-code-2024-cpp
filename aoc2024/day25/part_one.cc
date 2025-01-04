
module;
#include <bits/types/error_t.h>
#include <cmath>
#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unordered_set>
#include <utility>
#include <vector>

export module part_one;

using namespace std;

export namespace part_one {

void ParseInput(const string_view Input, vector<vector<int>> &Keys,
                vector<vector<int>> &Locks) {
  stringstream ss((string(Input)));
  string line;
  bool newItem = true;
  bool key = false;
  bool initialItem = true;
  vector<int> item;
  vector<int> keyReset{0, 0, 0, 0, 0};
  vector<int> lockReset{5, 5, 5, 5, 5};
  while (getline(ss, line, '\n')) {
    if (newItem) {
      if (!initialItem) {
        if (key) {
          Keys.push_back(item);
        } else {
          Locks.push_back(item);
        }
      }
      newItem = false;
      initialItem = false;
      if (line == "#####") {
        key = true;
        item = keyReset;
      } else {
        key = false;
        item = lockReset;
      }
    } else {
      if (line == "") {
        newItem = true;
        continue;
      }
      if (key) {
        stringstream ss2(line);
        for (int i = 0; i < 5; i++) {
          if (line[i] == '#') {
            item[i]++;
          }
        }
      } else {
        stringstream ss2(line);
        for (int i = 0; i < 5; i++) {
          if (line[i] == '.') {
            item[i]--;
          }
        }
      }
    }
  }
  if (key) {
    Keys.push_back(item);
  } else {
    Locks.push_back(item);
  }
}

uint64_t result(const string_view Input) {
  vector<vector<int>> keys;
  vector<vector<int>> locks;
  ParseInput(Input, keys, locks);
  uint64_t result = 0;
  for (auto const &key : keys) {
    for (auto const &lock : locks) {
      bool ok = true;
      for (int i = 0; i < 5; i++) {
        if (key[i] + lock[i] > 5) {
          ok = false;
          break;
        }
      }
      if (ok) {
        result++;
      }
    }
  }
  return result;
}
} // namespace part_one