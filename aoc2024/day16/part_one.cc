
module;
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_one;

struct PositionType {
  int32_t row;
  int32_t col;
  auto operator<=>(const PositionType &other) const = default;
  PositionType operator+(const PositionType &other) const {
    return PositionType{row + other.row, col + other.col};
  };
  PositionType operator-(const PositionType &other) const {
    return PositionType{row - other.row, col - other.col};
  };
  PositionType operator+=(const PositionType &other) const {
    return PositionType{row + other.row, col + other.col};
  };
  PositionType operator*(const int32_t &mul) const {
    return PositionType{row * mul, col * mul};
  };
};

constexpr PositionType up{-1, 0};
constexpr PositionType right{0, 1};
constexpr PositionType down{1, 0};
constexpr PositionType left{0, -1};

struct PathType {
  uint64_t score = 0;
  PositionType position;
  PositionType direction = right;
  std::set<PositionType> path{};
  std::vector<PositionType> orderedPath{};
};

using PathsType = std::vector<PathType>;
using DirectionsType = std::vector<PositionType>;

const DirectionsType directions{down, left, right, up};

struct KeyType {
  PositionType pos;
  PositionType dir;
  auto operator<=>(const KeyType &other) const = default;
};

export namespace part_one {
uint64_t result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};
  std::set<PositionType> walls{};
  PositionType start;
  PositionType end;
  int32_t row = 0;
  int32_t col = 0;
  int32_t rows = 0;
  int32_t cols = 0;
  PathType bestPath{};
  std::map<KeyType, uint64_t> bestScores;

  while (getline(ss, line, '\n')) {
    if (line == "") {

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
      case 'S':
        start = position;
        break;
      case 'E':
        end = position;
        break;
      default:
        break;
      }
      col++;
    }
    row++;
  }
  cols = col;
  rows = row;
  uint64_t lowScore = UINT64_MAX;
  PathsType paths{PathType{.position = start}};
  while (!paths.empty()) {
    auto path = paths.back();
    paths.pop_back();
    for (auto const &dir : directions) {
      if ((dir == up && path.direction == down) ||
          (dir == right && path.direction == left) ||
          (dir == down && path.direction == up) ||
          (dir == left && path.direction == right)) {
        continue;
      }
      if (!walls.contains(path.position + dir) &&
          !path.path.contains((path.position + dir))) {
        auto newPath = path;
        if (dir == newPath.direction) {
          newPath.score += 1;
        } else {
          newPath.score += 1001;
          newPath.path.insert(newPath.position);
        }
        if (newPath.score < lowScore) {
          newPath.direction = dir;
          newPath.position = newPath.position + dir;
          if (newPath.position == end) {
            lowScore = newPath.score;
            bestPath = newPath;
            std::cout << lowScore << ", " << paths.size() << std::endl;
          } else {
            if (!bestScores.contains(
                    KeyType{newPath.position, newPath.direction}) ||
                newPath.score <
                    bestScores[KeyType{newPath.position, newPath.direction}]) {
              bestScores.insert_or_assign(
                  KeyType{newPath.position, newPath.direction}, newPath.score);
              paths.push_back(newPath);
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (walls.contains(PositionType{i, j})) {
        std::cout << "#";
      } else if (bestPath.path.contains(PositionType{i, j})) {
        std::cout << "o";
      } else {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
  return lowScore;
}
} // namespace part_one