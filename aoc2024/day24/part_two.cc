
module;
#include <bits/types/error_t.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <utility>
#include <vector>

export module part_two;

using namespace std;

export namespace part_two {

void ParseInput(const string_view Input, map<string, bool> &KnownWires,
                map<string, tuple<string, string, string>> &Gates,
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

uint64_t Compute(map<string, bool> KnownWires,
                 map<string, tuple<string, string, string>> Gates,
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

string result(const string_view Input) {
  map<string, bool> knownWires;
  map<string, tuple<string, string, string>> gates;
  vector<string> unknownWires;
  ParseInput(Input, knownWires, gates, unknownWires);
  set<string> usedGates;
  map<int, pair<string, string>> As;
  map<int, pair<string, string>> Bs;
  map<int, pair<string, string>> Cs;
  map<int, pair<string, string>> Ds;

  // zn = An XOR Bn-1
  // Where,
  // An = xn XOR yn
  // Bn = Cn OR Dn
  // Cn = xn AND yn
  // Dn = An AND Cn-1
  // all subscripts are positive integers.
  // i.e.:
  // z0 = A0
  // z1 = A1 XOR B0 = A1 XOR C0
  // z2 = A2 XOR B1 = A2 XOR (C1 OR D1) = A2 XOR (C1 OR (A1 AND C0))
  // z3 = A3 XOR B3 = A3 XOR (C2 OR D2) = A3 XOR (C2 OR (A2 AND C1))
  // etc...

  for (auto const &gate : gates) {
    if (gate.first.starts_with('z')) {
      int index = stoi(gate.first.substr(1));

      vector<string> inputWires;
      string outputWire = gate.first;
      string gateType = get<0>(gate.second);
      string input1Wire = get<1>(gate.second);
      string input2Wire = get<2>(gate.second);

      cout << outputWire << " = " << input1Wire << " " << gateType << " "
           << input2Wire << endl;
      cout << "------------" << endl;

      inputWires.push_back(get<1>(gate.second));
      inputWires.push_back(get<2>(gate.second));
      while (!inputWires.empty()) {
        string inputWire = inputWires.back();
        inputWires.pop_back();
        if (gates.contains(inputWire) && !usedGates.contains(inputWire)) {
          usedGates.insert(inputWire);
          auto nextGate = gates[inputWire];
          cout << inputWire << " = " << get<1>(nextGate) << " "
               << get<0>(nextGate) << " " << get<2>(nextGate) << endl;
          inputWires.push_back(get<1>(nextGate));
          inputWires.push_back(get<2>(nextGate));
        }
      }
      cout << "------------" << endl;
    }
  }

  return "OK";
}
} // namespace part_two