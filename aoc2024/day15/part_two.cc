

module;
#include <cstdint>
#include <iostream>
#include <set>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_two;

struct PositionType {
  int32_t row;
  int32_t col;
  auto operator<=>(const PositionType &other) const = default;
  PositionType operator+(const PositionType &other) const {
    return PositionType{row + other.row, col + other.col};
  };
  PositionType operator*(const int32_t &mul) const {
    return PositionType{row * mul, col * mul};
  };
};

struct DirectionType {
  PositionType direction;
  char character;
};

constexpr DirectionType up{PositionType{-1, 0}, '^'};
constexpr DirectionType right{PositionType{0, 1}, '>'};
constexpr DirectionType down{PositionType{1, 0}, 'v'};
constexpr DirectionType left{PositionType{0, -1}, '<'};

export namespace part_two {
uint64_t result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};
  std::set<PositionType> walls{};
  std::set<PositionType> wideBoxes{};
  std::vector<PositionType> checkQueue{};
  std::vector<PositionType> moveQueue{};
  PositionType robot;
  int32_t row = 0;
  int32_t col = 0;
  int32_t rows = 0;
  int32_t cols = 0;
  char command;

  while (getline(ss, line, '\n')) {
    if (line == "") {
      cols = col;
      rows = row;
      break;
    }
    std::stringstream ss2(line);
    col = 0;
    for (char square : line) {
      ss2 >> square;
      PositionType position{row, col};
      switch (square) {
      case '#':
        walls.insert(position);
        walls.insert(position + right.direction);
        break;
      case 'O':
        wideBoxes.insert(position);
        break;
      case '@':
        robot = position;
        break;
      default:
        break;
      }
      col += 2;
    }
    row++;
  }
  PositionType dir;
  while (ss >> command) {
    // std::cout << command << std::endl;
    switch (command) {
    case up.character:
      dir = up.direction;
      break;
    case right.character:
      dir = right.direction;
      break;
    case down.character:
      dir = down.direction;
      break;
    case left.character:
      dir = left.direction;
      break;
    default:
      break;
    }

    if (!walls.contains(robot + dir)) {
      checkQueue.clear();
      moveQueue.clear();
      if (wideBoxes.contains(robot + dir)) {
        checkQueue.push_back(robot + dir);
      } else if (wideBoxes.contains(robot + dir + left.direction)) {
        checkQueue.push_back(robot + dir + left.direction);
      }
      bool blockage = false;

      while (!checkQueue.empty()) {
        auto boxPosition = checkQueue.back();
        moveQueue.push_back(boxPosition);
        checkQueue.pop_back();
        auto newPosition = boxPosition + dir;

        if (walls.contains(newPosition) ||
            walls.contains(newPosition + right.direction)) {
          blockage = true;
          break;
        }
        if (wideBoxes.contains(newPosition)) {
          checkQueue.push_back(newPosition);
        }
        if (wideBoxes.contains(newPosition + right.direction) &&
            dir != left.direction) {
          checkQueue.push_back(newPosition + right.direction);
        }
        if (wideBoxes.contains(newPosition + left.direction) &&
            dir != right.direction) {
          checkQueue.push_back(newPosition + left.direction);
        }
      }
      if (!blockage) {
        uint64_t moveSize = moveQueue.size();
        for (uint64_t i = 0; i < moveSize; i++) {
          auto move = moveQueue.back();
          moveQueue.pop_back();
          wideBoxes.erase(move);
          wideBoxes.insert(move + dir);
        }
        robot = robot + dir;
      }
    }
    /* for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (wideBoxes.contains(PositionType{i, j})) {
          std::cout << '[';
        } else if (wideBoxes.contains(PositionType{i, j - 1})) {
          std::cout << ']';
        } else if (walls.contains(PositionType{i, j})) {
          std::cout << '#';
        } else if (robot == PositionType{i, j}) {
          std::cout << '@';
        } else {
          std::cout << '.';
        }
      }
      std::cout << std::endl;
    } */
  }
  uint64_t result = 0;
  for (auto const &box : wideBoxes) {
    result += box.row * 100 + box.col;
  }
  return result;
}
} // namespace part_two