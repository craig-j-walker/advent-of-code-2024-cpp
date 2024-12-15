
module;
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_one;

export namespace part_one {

struct PositionType {
  uint32_t x;
  uint32_t y;
  auto operator<=>(const PositionType &other) const = default;
};

struct CostType {
  uint64_t tokens;
  uint64_t presses;
  auto operator<=>(const CostType &other) const = default;
};

struct ElementType {
  PositionType position;
  CostType cost;
  auto operator<=>(const ElementType &other) const = default;
};

enum Button { A, B };

struct InstructionType {
  PositionType buttonA;
  PositionType buttonB;
  PositionType prize;
  uint64_t cheapest = std::numeric_limits<uint64_t>::max();
  bool prizeFound = false;
};

using InstructionsType = std::vector<InstructionType>;
using QueueType = std::vector<ElementType>;
using MemoType = std::map<PositionType, CostType>;

void Increment(ElementType &E, Button Button, InstructionType &Instruction,
               QueueType &Q) {
  E.cost.presses += 1;
  if (Button == Button::A) {
    E.cost.tokens += 3;
    E.position.x += Instruction.buttonA.x;
    E.position.y += Instruction.buttonA.y;
  } else {
    E.cost.tokens += 1;
    E.position.x += Instruction.buttonB.x;
    E.position.y += Instruction.buttonB.y;
  }

  if (E.cost.presses < 100 && E.cost.tokens < Instruction.cheapest &&
      E.position.x < Instruction.prize.x &&
      E.position.y < Instruction.prize.y) {
    if (E.position == Instruction.prize &&
        E.cost.tokens < Instruction.cheapest) {
      Instruction.cheapest = E.cost.tokens;
    } else {
      Q.push_back(E);
    }
  }
}

uint64_t result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};
  InstructionsType instructions{};

  int i = 0;

  while (std::getline(ss, line, '\n')) {
    std::stringstream ss2(line);
    int instructionRow = i % 4;
    std::string blurb;
    switch (instructionRow) {
    case 0: {
      InstructionType instruction;
      ss2 >> blurb;
      ss2 >> blurb;
      ss2 >> blurb;
      instruction.buttonA.x = stoi(blurb.substr(2, blurb.length() - 3));
      ss2 >> blurb;
      instruction.buttonA.y = stoi(blurb.substr(2, blurb.length() - 2));
      instructions.push_back(instruction);
      break;
    }
    case 1: {
      ss2 >> blurb;
      ss2 >> blurb;
      ss2 >> blurb;
      instructions[i / 4].buttonB.x = stoi(blurb.substr(2, blurb.length() - 3));
      ss2 >> blurb;
      instructions[i / 4].buttonB.y = stoi(blurb.substr(2, blurb.length() - 2));
      break;
    }
    case 2: {
      ss2 >> blurb;
      ss2 >> blurb;
      instructions[i / 4].prize.x = stoi(blurb.substr(2, blurb.length() - 3));
      ss2 >> blurb;
      instructions[i / 4].prize.y = stoi(blurb.substr(2, blurb.length() - 2));
      break;
    }
    default: {
      break;
    }
    }
    i++;
  }

  uint64_t spend = 0;
  for (auto &i : instructions) {
    for (int64_t numA = 0; numA <= i.prize.x / i.buttonA.x &&
                           numA <= i.prize.y / i.buttonA.y && numA <= 100;
         numA++) {

      int32_t x = numA * i.buttonA.x;
      int32_t y = numA * i.buttonA.y;

      int32_t numBX = (i.prize.x - x) / i.buttonB.x;
      int32_t numBY = (i.prize.y - y) / i.buttonB.y;
      if (numBX == numBY && numBX <= 100 && numBX >= 0 &&
          numA * 3 + numBX < i.cheapest &&
          (numA * i.buttonA.x + numBX * i.buttonB.x == i.prize.x) &&
          (numA * i.buttonA.y + numBX * i.buttonB.y == i.prize.y)) {

        i.cheapest = numA * 3 + numBX;
        i.prizeFound = true;
      }
    }
    if (i.prizeFound) {
      spend += i.cheapest;
    }
  }
  return spend;
}
} // namespace part_one