
module;
#include <cstdint>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

export module part_one;

export namespace part_one {

using positionType = std::tuple<uint32_t, uint32_t>;
using directionType = std::tuple<uint32_t, uint32_t>;
using mapSquareType = std::tuple<char, bool>;
using mapType = std::map<positionType, mapSquareType>;
using guardType = std::tuple<positionType, directionType>;

// Function to add two tuples element-wise
template <typename... Ts, size_t... Is>
auto add_tuples_impl(const std::tuple<Ts...> &t1, const std::tuple<Ts...> &t2,
                     std::index_sequence<Is...>) {
  return std::make_tuple((std::get<Is>(t1) + std::get<Is>(t2))...);
}
template <typename... Ts>
auto add_tuples(const std::tuple<Ts...> &t1, const std::tuple<Ts...> &t2) {
  return add_tuples_impl(t1, t2, std::index_sequence_for<Ts...>{});
}

uint64_t result(const std::string_view input) {
  uint64_t answer = 0;
  mapType map;
  std::string row;
  std::stringstream ss((std::string(input)));
  guardType guard;
  uint32_t i = 0;
  const directionType up{-1, 0};
  const directionType right{0, 1};
  const directionType down{1, 0};
  const directionType left{0, -1};

  while (std::getline(ss, row, '\n')) {

    std::stringstream rowStream(row);
    char square;
    std::vector<char> mapRow;

    for (uint32_t j = 0; j < row.size(); j++) {
      rowStream >> square;
      positionType position{i, j};

      if (square == '^' || square == '>' || square == 'v' || square == '<') {

        mapSquareType mapSquare{'.', true};
        directionType direction;
        if (square == '^') {
          direction = up;
        } else if (square == '>') {
          direction = right;
        } else if (square == 'v') {
          direction = down;
        } else if (square == '<') {
          direction = left;
        }
        guard = guardType{position, direction};
        map.insert(std::make_pair(position, mapSquare));
      } else {
        mapSquareType mapSquare{square, false};
        map.insert(std::make_pair(position, mapSquare));
      }
    }
    i++;
  }
  bool exit = false;
  while (!exit) {
    positionType nextPosition =
        add_tuples(std::get<0>(guard), std::get<1>(guard));
    if (map.contains(nextPosition)) {
      char square = std::get<0>(map.at(nextPosition));
      if (square == '.') {
        mapSquareType updatedSquare{'.', true};
        map.at(nextPosition) = updatedSquare;
        std::get<0>(guard) = nextPosition;
      } else if (square == '#') {
        directionType direction = std::get<1>(guard);
        if (direction == up) {
          direction = right;
        } else if (direction == right) {
          direction = down;
        } else if (direction == down) {
          direction = left;
        } else if (direction == left) {
          direction = up;
        }
        std::get<1>(guard) = direction;
      } else {
        exit = true;
      }
    } else {
      exit = true;
    }
  }
  for (auto &mapSquare : map) {
    if (std::get<1>(mapSquare.second)) {
      answer++;
    }
  }

  return answer;
}
} // namespace part_one