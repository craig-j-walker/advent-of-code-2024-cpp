
module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_two;

using namespace std;

export namespace part_two {

void ParseInput(const string_view Input,
                vector<uint64_t> &InitialSecretNumbers) {
  stringstream ss((string(Input)));
  string line;

  while (getline(ss, line, '\n')) {
    InitialSecretNumbers.push_back(stoll(line));
  }
}

void MixAndPrune(uint64_t &SecretNumber, uint64_t Result) {
  SecretNumber = SecretNumber ^ Result;   // mix
  SecretNumber = SecretNumber & 16777215; // prune
}

void Evolve(uint64_t &SecretNumber) {
  uint64_t result = SecretNumber << 6;
  MixAndPrune(SecretNumber, result);
  result = SecretNumber >> 5;
  MixAndPrune(SecretNumber, result);
  result = SecretNumber << 11;
  MixAndPrune(SecretNumber, result);
}

uint64_t result(const string_view input) {
  vector<uint64_t> initialSecretNumbers{};
  ParseInput(input, initialSecretNumbers);

  map<pair<vector<int>, uint64_t>, int> changeMap{};

  for (auto const &initialSecretNumber : initialSecretNumbers) {
    vector<int> changes{};
    uint64_t sn = initialSecretNumber;
    for (int i = 0; i < 1999; i++) {
      int initialPrice = sn % 10;
      Evolve(sn);
      int newPrice = sn % 10;
      changes.push_back(newPrice - initialPrice);
      if (changes.size() > 4) {
        changes.erase(changes.begin());
        if (!changeMap.contains(make_pair(changes, initialSecretNumber))) {
          changeMap.insert(
              make_pair(make_pair(changes, initialSecretNumber), newPrice));
        }
      }
    }
  }
  uint64_t mostBananas = 0;
  for (auto const &mapEntry : changeMap) {
    uint64_t bananas = 0;
    for (auto const &initialSecretNumber : initialSecretNumbers) {
      if (changeMap.contains(
              make_pair(mapEntry.first.first, initialSecretNumber))) {
        bananas +=
            changeMap[make_pair(mapEntry.first.first, initialSecretNumber)];
      }
    }
    if (bananas > mostBananas) {
      mostBananas = bananas;
    }
  }

  return mostBananas;
}
} // namespace part_two