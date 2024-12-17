
module;
#include <cstdint>
#include <iostream>
#include <set>
#include <sstream>
#include <string_view>
#include <sys/types.h>

export module part_one;

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

export namespace part_one {
uint64_t result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};
  std::set<PositionType> walls{};
  std::set<PositionType> boxes{};
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
        break;
      case 'O':
        boxes.insert(position);
        break;
      case '@':
        robot = position;
        break;
      default:
        break;
      }
      col++;
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

      int32_t i = 1;
      while (boxes.contains(robot + dir * i) &&
             ((dir == up.direction && (robot + dir * i).row > 1) ||
              (dir == right.direction && (robot + dir * i).col < cols - 2) ||
              (dir == down.direction && (robot + dir * i).row < rows - 2) ||
              (dir == left.direction && (robot + dir * i).col > 1))) {
        i++;
      }
      if (walls.contains(robot + dir * i)) {
        i = 1;
      }

      if (!(boxes.contains(robot + dir * i) &&
            !(walls.contains(robot + dir * i)))) {
        while (i >= 2) {
          boxes.erase(robot + dir * (i - 1));
          boxes.insert(robot + dir * i);
          i--;
        }
      }
      if (!(boxes.contains(robot + dir))) {
        robot = robot + dir;
      }
    }
    /*  for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
         if (boxes.contains(PositionType{i, j})) {
           std::cout << 'O';
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
  for (auto const &box : boxes) {
    result += box.row * 100 + box.col;
  }
  return result;
}
} // namespace part_one