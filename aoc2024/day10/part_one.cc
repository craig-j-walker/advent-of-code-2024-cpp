module;

#include <cstdint>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string_view>
#include <sys/types.h>
#include <utility>

export module part_one;

export namespace part_one {

struct CoordinateType {
  int32_t row;
  int32_t col;
  CoordinateType operator+(const CoordinateType &other) const {
    return CoordinateType{row + other.row, col + other.col};
  }
  friend auto operator<=>(const CoordinateType &,
                          const CoordinateType &) = default;
};

struct MapSquareType {
  CoordinateType coordinate;
  int8_t height;
  friend auto operator<=>(const MapSquareType &,
                          const MapSquareType &) = default;
};

struct GoodTrailType {
  MapSquareType start;
  MapSquareType end;
  friend auto operator<=>(const GoodTrailType &,
                          const GoodTrailType &) = default;
};

using TrailType = std::vector<MapSquareType>;
using TrailsType = std::vector<TrailType>;
using MapType = std::map<CoordinateType, int8_t>;

const CoordinateType up{-1, 0};
const CoordinateType right{0, 1};
const CoordinateType down{1, 0};
const CoordinateType left{0, -1};
const std::vector<CoordinateType> directions{up, down, left, right};

uint64_t result(const std::string_view input) {
  MapType map;
  TrailsType trails;
  std::stringstream ss((std::string(input)));
  std::vector<char> mapSquares(input.begin(), input.end());
  std::string line;
  int32_t row = 0;
  int32_t col = 0;

  while (std::getline(ss, line, '\n')) {
    col = 0;
    for (auto &square : line) {
      if (square != '\n') {
        std::string space;
        space += square;
        int8_t height = std::stoi(space);
        CoordinateType coordinate{row, col};
        map.insert(std::make_pair(coordinate, height));
        if (height == 9) {
          TrailType trail;
          trail.push_back(MapSquareType{coordinate, height});
          trails.push_back(trail);
        }
      }
      col++;
    }
    row++;
  }

  std::set<GoodTrailType> goodTrails;

  while (!trails.empty()) {
    TrailType trail = trails.back();
    trails.pop_back();
    if (trail.back().height == 0) {
      GoodTrailType goodTrail{trail.front(), trail.back()};
      goodTrails.insert(goodTrail);
    } else {
      for (auto const &direction : directions) {
        CoordinateType newCoordinate = trail.back().coordinate + direction;
        if (map.contains(newCoordinate)) {
          int8_t newHeight = trail.back().height - 1;
          if (map[newCoordinate] == newHeight) {
            TrailType newTrail = trail;
            newTrail.push_back(MapSquareType{newCoordinate, newHeight});
            trails.push_back(newTrail);
          }
        }
      }
    }
  }

  return goodTrails.size();
}

} // namespace part_one