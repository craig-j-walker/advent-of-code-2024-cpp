

module;
#include <algorithm>
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

export module part_two;

export namespace part_two {

uint64_t combo(uint8_t &operand, std::vector<uint64_t> &Registers) {
  switch (operand) {
  case 0:
  case 1:
  case 2:
  case 3:
    return operand;
  case 4:
    return Registers[0];
  case 5:
    return Registers[1];
  case 6:
    return Registers[2];
  default:
    throw std::exception();
    return 0;
  }
}
uint64_t result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};
  std::vector<uint8_t> Program;
  std::string prog;
  uint64_t ptr = 0;
  uint8_t opcode;
  uint8_t operand;
  std::vector<uint64_t> Registers;
  std::string Output;
  std::vector<uint64_t> Initial;
  std::vector<uint64_t> answers;

  getline(ss, line, '\n');
  Registers.push_back(stoi(line.substr(12)));
  getline(ss, line, '\n');
  Registers.push_back(stoi(line.substr(12)));
  getline(ss, line, '\n');
  Registers.push_back(stoi(line.substr(12)));
  getline(ss, line, '\n');
  getline(ss, line, '\n');
  std::stringstream ss2(line.substr(9));

  Initial = Registers;
  while (getline(ss2, line, ',')) {
    Program.push_back(stoi(line));
  }
  for (char p : Program) {
    prog += std::to_string(p);
  }
  std::vector<std::tuple<uint64_t, uint8_t>> regA{
      std::make_tuple(0, prog.size() - 1)};
  uint8_t depth;
  uint64_t start;
  uint64_t reg_a;
  while (!regA.empty()) {

    Registers = Initial;
    reg_a = std::get<0>(regA.back());
    depth = std::get<1>(regA.back());
    regA.pop_back();
    for (uint64_t j = 0; j < 8; ++j) {
      Registers[0] = reg_a | (j << (3 * depth));
      Registers[1] = 0;
      Registers[2] = 0;
      start = Registers[0];
      ptr = 0;
      Output.clear();
      while (ptr < Program.size()) {
        opcode = Program[ptr];
        operand = Program[ptr + 1];
        ptr += 2;
        switch (opcode) {
        case 0: // adv
          Registers[0] = Registers[0] >> combo(operand, Registers);
          break;
        case 1: // bxl
          Registers[1] = Registers[1] ^ operand;
          break;
        case 2: // bst
          Registers[1] = combo(operand, Registers) % 8;
          break;
        case 3: // jnz
          if (Registers[0] != 0) {
            ptr = operand;
          }
          break;
        case 4:
          Registers[1] = Registers[1] ^ Registers[2];
          break;
        case 5:
          Output += std::to_string(combo(operand, Registers) % 8);
          break;
        case 6:
          Registers[1] = Registers[0] >> combo(operand, Registers);
          break;
        case 7:
          Registers[2] = Registers[0] >> combo(operand, Registers);
          break;
        default:
          break;
        }
      }
      if (Output.size() == prog.size()) {
        if (Output == prog) {

          std::cout << "start: " << start << ", output: " << Output
                    << ", program: " << prog
                    << ", difference: " << std::stoll(prog) - std::stoll(Output)
                    << std::endl;
          answers.push_back(start);
        }
        if (Output[depth] == prog[depth]) {
          regA.push_back(std::make_tuple(start, depth - 1));
          std::cout << "start: " << start << ", output: " << Output
                    << ", program: " << prog
                    << ", difference: " << std::stoll(prog) - std::stoll(Output)
                    << std::endl;
        }
      }
    }
  }
  return *std::min_element(answers.begin(), answers.end());
}
} // namespace part_two