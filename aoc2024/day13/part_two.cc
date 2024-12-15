
module;
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_two;

export namespace part_two {

struct PositionType {
  long long x;
  long long y;
  auto operator<=>(const PositionType &other) const = default;
};

struct CostType {
  long long tokens;
  long long presses;
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
  long long cheapest = std::numeric_limits<long long>::max();
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

long long result(const std::string_view input) {
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
      instructions[i / 4].prize.x =
          stoi(blurb.substr(2, blurb.length() - 3)) + 10000000000000;
      ss2 >> blurb;
      instructions[i / 4].prize.y =
          stoi(blurb.substr(2, blurb.length() - 2)) + 10000000000000;
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

    long long det = (i.buttonA.x * i.buttonB.y) - (i.buttonA.y * i.buttonB.x);
    long long a = (i.prize.x * i.buttonB.y - i.prize.y * i.buttonB.x) / det;
    long long b = (i.prize.y * i.buttonA.x - i.prize.x * i.buttonA.y) / det;

    if ((i.buttonA.x * a + i.buttonB.x * b == i.prize.x) &&
        (i.buttonA.y * a + i.buttonB.y * b == i.prize.y)) {

      i.cheapest = a * 3 + b;
      spend += i.cheapest;
    }
  }
  return spend;
}
} // namespace part_two