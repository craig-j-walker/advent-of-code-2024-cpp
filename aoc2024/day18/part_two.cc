module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_two;

export namespace part_two {

struct Position {
  int32_t row;
  int32_t col;
  auto operator<=>(const Position &other) const = default;
  auto operator+(const Position &other) {
    return Position{row + other.row, col + other.col};
  };
};
struct Safe {
  uint64_t score;
  bool visited;
};

constexpr Position up{-1, 0};
constexpr Position right{0, 1};
constexpr Position down{1, 0};
constexpr Position left{0, -1};

const std::vector<Position> directions{up, down, left, right};

std::string result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};
  std::set<Position> corruptions;
  std::vector<Position> corruptionlist;
  Position us{0, 0};
  Position exit{70, 70};
  Position blockage;
  std::map<Position, Safe> map{};

  while (getline(ss, line, '\n')) {
    int32_t col = stoll(line.substr(0, line.find(",", 0)));
    int32_t row = stoll(line.substr(line.find(",", 0) + 1));
    corruptionlist.push_back(Position{row, col});
  }

  bool blocked = false;
  for (int i = 0; i < 1024; i++) {
    corruptions.insert(corruptionlist[i]);
  }

  for (int i = 1024; i < corruptionlist.size(); i++) {
    blockage = corruptionlist[i];
    corruptions.insert(blockage);
    blocked = true;
    map.clear();
    map.insert({std::make_pair(us, Safe{0, false})});
    std::vector<Position> positions{us};
    uint64_t bestScore = UINT64_MAX;

    while (!positions.empty()) {
      Position pos = positions.back();
      positions.pop_back();
      map[pos].visited = true;

      for (auto const &dir : directions) {
        Position nextPos = pos + dir;
        uint64_t nextScore = map[pos].score + 1;
        if (nextScore >= bestScore || corruptions.contains(nextPos)) {
          continue;
        }
        if (map.contains(nextPos)) {
          if (nextScore < map[nextPos].score) {
            if (nextPos == exit) {
              blocked = false;
              bestScore = nextScore;
            } else {
              {
                map[nextPos].score = nextScore;
                if (!map[nextPos].visited) {
                  positions.insert(positions.begin(), nextPos);
                }
              }
            }
          }
        } else if (nextPos.col >= 0 && nextPos.col <= exit.col &&
                   nextPos.row >= 0 && nextPos.row <= exit.row) {
          map.insert(std::make_pair(nextPos, nextScore));
          if (nextPos == exit) {
            blocked = false;
            bestScore = nextScore;
          } else {
            positions.insert(positions.begin(), nextPos);
          }
        }
        if (!blocked) {
          break;
        }
      }
      if (!blocked) {
        break;
      }
    }
    std::cout << i << std::endl;
    if (blocked) {
      break;
    }
  }
  for (int32_t i = 0; i <= exit.row; i++) {
    for (int32_t j = 0; j <= exit.col; j++) {
      if (Position{i, j} == exit) {
        std::cout << "EEE";
      } else if (Position{i, j} == us) {
        std::cout << "SSS";
      } else if (map[Position{i, j}].visited) {
        std::cout << std::setw(3) << map[Position{i, j}].score;
      } else if (corruptions.contains(Position{i, j})) {
        std::cout << "###";
      } else {
        std::cout << "...";
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
  std::stringstream answer;
  answer << blockage.col << "," << blockage.row;
  return answer.str();
}

} // namespace part_two