

module;
#include <cstdint>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unordered_map>
#include <utility>
#include <vector>

export module part_one;

export namespace part_one {

struct PositionType {
  int32_t row;
  int32_t col;

  bool operator==(const PositionType &other) const {
    return row == other.row && col == other.col;
  };
  PositionType operator+(const PositionType &other) const {
    return PositionType{row + other.row, col + other.col};
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
};

struct BedType {
  char veg;
  bool visited;
};

using MapType = std::unordered_map<PositionType, BedType, PositionTypeKeyHash>;
using PlotsType = std::vector<PlotType>;
using PositionsType = std::vector<PositionType>;

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
    plot = PlotType{map[pos].veg, 0, 0};

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
    totalPrice += plot.perimeter * plot.area;
    std::cout << plot.veg << "[" << bed.row << "," << bed.col
              << "]: " << totalPrice << " (" << plot.perimeter << " x "
              << plot.area << " = " << plot.area * plot.perimeter << ")"
              << std::endl;
  }
  for (auto ms : map) {
    if (!ms.second.visited) {
      std::cout << ms.second.veg << "[" << ms.first.row << "," << ms.first.col
                << "] has not been visited!" << std::endl;
    }
  }
  return totalPrice;
}
} // namespace part_one