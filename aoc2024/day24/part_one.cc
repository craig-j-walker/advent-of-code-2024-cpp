
module;
#include <bits/types/error_t.h>
#include <cmath>
#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unordered_map>
#include <utility>
#include <vector>

export module part_one;

using namespace std;

export namespace part_one {

void ParseInput(const string_view Input,
                unordered_map<string, bool> &KnownWires,
                unordered_map<string, tuple<string, string, string>> &Gates,
                vector<string> &UnknownWires) {
  stringstream ss((string(Input)));
  string line;
  bool inputsCollected = false;

  while (getline(ss, line, '\n')) {
    if (!inputsCollected) {
      if (line == "") {
        inputsCollected = true;
        continue;
      }
      KnownWires.insert(
          make_pair(line.substr(0, 3), (line.substr(5, 1) == "1")));
    } else {
      stringstream ss2(line);
      string input1;
      string gate;
      string input2;
      string arrows;
      string output;
      ss2 >> input1;
      ss2 >> gate;
      ss2 >> input2;
      ss2 >> arrows;
      ss2 >> output;
      Gates.insert(make_pair(output, make_tuple(gate, input1, input2)));
      UnknownWires.push_back(output);
    }
  }
}

uint64_t Compute(unordered_map<string, bool> KnownWires,
                 unordered_map<string, tuple<string, string, string>> Gates,
                 vector<string> UnknownWires) {
  while (!UnknownWires.empty()) {
    string output = UnknownWires.back();
    tuple<string, string, string> gate = Gates[output];
    UnknownWires.pop_back();
    string gateType = get<0>(gate);
    string input1 = get<1>(gate);
    string input2 = get<2>(gate);
    if (!KnownWires.contains(input1) || !KnownWires.contains(input2)) {
      UnknownWires.insert(UnknownWires.begin(), output);
    } else if (gateType == "AND") {
      KnownWires.insert(
          make_pair(output, KnownWires[input1] && KnownWires[input2]));
    } else if (gateType == "OR") {
      KnownWires.insert(
          make_pair(output, KnownWires[input1] || KnownWires[input2]));
    } else {

      KnownWires.insert(
          make_pair(output, KnownWires[input1] != KnownWires[input2]));
    }
  }
  int i = 0;
  uint64_t result = 0;
  while (true) {
    string wire{};
    string wireNumber = to_string(i);
    if (wireNumber.length() == 1) {
      wire = "z0" + wireNumber;
    } else {
      wire = "z" + wireNumber;
    }
    if (!KnownWires.contains(wire)) {
      return result;
    }
    result += KnownWires[wire] * pow(2, i);
    i++;
  }
}

uint64_t result(const string_view Input) {
  unordered_map<string, bool> knownWires;
  unordered_map<string, tuple<string, string, string>> gates;
  vector<string> unknownWires;
  ParseInput(Input, knownWires, gates, unknownWires);
  return Compute(knownWires, gates, unknownWires);
}
} // namespace part_one