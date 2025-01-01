
module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_one;

using namespace std;

export namespace part_one {

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
  uint64_t sum = 0;
  for (auto &sn : initialSecretNumbers) {
    for (int i = 0; i < 2000; i++) {
      Evolve(sn);
    }
    sum += sn;
  }
  return sum;
}
} // namespace part_one