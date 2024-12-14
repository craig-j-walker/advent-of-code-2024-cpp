module;
#include <cstdint>
#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unordered_map>
#include <utility>
#include <vector>

export module part_two;

export namespace part_two {

struct PositionType {
  int32_t row;
  int32_t col;

  auto operator<=>(const PositionType &other) const = default;

  PositionType operator+(const PositionType &other) const {
    return PositionType{row + other.row, col + other.col};
  }
  PositionType operator-(const PositionType &other) const {
    return PositionType{row - other.row, col - other.col};
  }
};

struct PositionTypeKeyHash {
  std::size_t operator()(const PositionType &key) const {
    return std::hash<int32_t>()(key.row) ^ std::hash<int32_t>()(key.col);
  }
};

struct PlotType {
  char veg;
  uint64_t area;
  uint64_t perimeter;
  std::set<PositionType> positions;
};

struct BedType {
  char veg;
  bool visited;
};

using MapType = std::unordered_map<PositionType, BedType, PositionTypeKeyHash>;
using PlotsType = std::vector<PlotType>;
using PositionsType = std::vector<PositionType>;
using PerimeterType = std::set<PositionType>;

const PositionType up{-1, 0};
const PositionType right{0, 1};
const PositionType down{1, 0};
const PositionType left{0, -1};

const std::vector<PositionType> directions{up, right, down, left};

uint64_t result(const std::string_view input) {
  std::stringstream ss{};

  ss << std::string(input);
  std::string line{};
  char veg;
  MapType map{};
  PositionsType positions{};
  int32_t row = 0;
  int32_t col = 0;
  while (std::getline(ss, line)) {
    std::stringstream ss2{};
    ss2 << line;
    col = 0;
    while (ss2 >> veg) {
      map.insert(std::make_pair(PositionType{row, col}, BedType{veg, false}));
      positions.push_back(PositionType{row, col});
      col++;
    }
    row++;
  }

  uint64_t totalPrice = 0;
  PositionType pos{};
  PositionType bed{};
  BedType other{};
  std::vector<PositionType> beds{};
  PlotType plot{};
  int64_t posSize = 0;
  while (true) {
    beds.clear();

    posSize = positions.size();
    for (int i = 0; i < posSize; i++) {
      pos = positions.front();
      if (map[pos].visited) {
        positions.push_back(pos);
        positions.erase(positions.begin());
        pos = positions.front();
      } else {
        break;
      }
    }

    if (map[pos].visited) {
      break;
    }

    beds.push_back(pos);
    plot = PlotType{map[pos].veg, 0, 0, {}};

    while (!beds.empty()) {
      int bedsSize = beds.size();
      for (int i = 0; i < bedsSize; i++) {
        bed = beds.back();
        if (!map[beds.back()].visited) {
          beds.pop_back();
          break;
        }
        beds.pop_back();
      }
      if (map[bed].visited) {
        break;
      }
      plot.positions.insert(bed);
      map[bed].visited = true;
      plot.area += 1;
      for (auto dir : directions) {
        if (map.contains(bed + dir)) {
          other = map[bed + dir];
          if (plot.veg == other.veg) {
            if (!other.visited) {
              beds.push_back(bed + dir);
            }
          } else {
            plot.perimeter += 1;
          }
        } else {
          plot.perimeter += 1;
        }
      }
    }
    // find a corner
    PositionType pos;
    PositionType sideDir;
    PerimeterType perimeter;
    PositionType dir;
    bool startFound;
    PositionType startPos;
    PositionType startDir;
    uint64_t sides = 0;
    while (true) {
      startFound = false;
      for (auto const &position : plot.positions) {
        for (auto const &direction : directions) {
          if ((!map.contains(position + direction) ||
               (map[position + direction].veg != plot.veg)) &&
              !perimeter.contains(position + direction)) {
            perimeter.insert(position + direction);
            pos = position;
            startPos = position;
            sideDir = direction;
            startFound = true;
            break;
          }
        }
        if (startFound) {
          break;
        }
      }
      if (!startFound) {
        break;
      }

      if (sideDir == up) {
        dir = right;
        startDir = right;
      } else if (sideDir == right) {
        dir = down;
        startDir = down;
      } else if (sideDir == down) {
        dir = left;
        startDir = left;
      } else {
        dir = up;
        startDir = up;
      }
      while (true) {
        if (plot.positions.contains(pos + dir)) {
          if (!map.contains(pos + dir + sideDir) ||
              (map[pos + dir + sideDir].veg != plot.veg)) {
            if (!perimeter.contains(pos + dir + sideDir)) {
              perimeter.insert(pos + dir + sideDir);
            }
            pos = pos + dir;
          } else {
            pos = pos + dir + sideDir;
            if (sideDir == up) {
              dir = up;
              sideDir = left;
            } else if (sideDir == left) {
              dir = left;
              sideDir = down;
            } else if (sideDir == down) {
              dir = down;
              sideDir = right;
            } else {
              dir = right;
              sideDir = up;
            }
            sides++;
          }
        } else {
          if (!perimeter.contains(pos + dir)) {
            perimeter.insert(pos + dir);
          }
          if (sideDir == up) {
            dir = down;
            sideDir = right;
          } else if (sideDir == left) {
            dir = right;
            sideDir = up;
          } else if (sideDir == down) {
            dir = up;
            sideDir = left;
          } else {
            dir = left;
            sideDir = down;
          }
          sides++;
        }
        if (dir == startDir && pos == startPos) {
          if (map.contains(pos - dir) && (map[pos - dir].veg == plot.veg)) {
            // sides--;
          }
          break;
        }
      }
    }
    totalPrice += sides * plot.area;
    std::cout << plot.veg << "[" << bed.row << "," << bed.col
              << "]: " << totalPrice << " (" << plot.area << " x " << sides
              << " = " << plot.area * sides << ")" << std::endl;
  }
  for (auto ms : map) {
    if (!ms.second.visited) {
      std::cout << ms.second.veg << "[" << ms.first.row << "," << ms.first.col
                << "] has not been visited!" << std::endl;
    }
  }
  return totalPrice;
}
} // namespace part_two