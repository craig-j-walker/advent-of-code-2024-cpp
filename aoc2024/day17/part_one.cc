

module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <exception>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_one;

export namespace part_one {

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
std::string result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};
  std::vector<uint8_t> Program;
  uint64_t ptr = 0;
  uint8_t opcode;
  uint8_t operand;
  std::vector<uint64_t> Registers;
  std::string output;

  getline(ss, line, '\n');
  Registers.push_back(stoi(line.substr(12)));
  getline(ss, line, '\n');
  Registers.push_back(stoi(line.substr(12)));
  getline(ss, line, '\n');
  Registers.push_back(stoi(line.substr(12)));
  getline(ss, line, '\n');
  getline(ss, line, '\n');
  std::stringstream ss2(line.substr(9));
  while (getline(ss2, line, ',')) {
    Program.push_back(stoi(line));
  }

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
      output += std::to_string(combo(operand, Registers) % 8);
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
  return output;
}
} // namespace part_one