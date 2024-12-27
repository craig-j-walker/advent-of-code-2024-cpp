module;

#include <bits/types/error_t.h>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>
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

struct PositionHash {
  std::size_t operator()(const Position &p) const {
    return std::hash<int32_t>()(p.row) ^ (std::hash<int32_t>()(p.col) << 1);
  }
};

enum TrackType { track, cheat1, cheat2 };

struct Info {
  int64_t time = 0;
  bool visited;
  TrackType type;
};

constexpr Position up{-1, 0};
constexpr Position right{0, 1};
constexpr Position down{1, 0};
constexpr Position left{0, -1};

const std::vector<Position> directions{up, down, left, right};

void ParseInput(const std::string_view Input,
                std::unordered_map<Position, Info, PositionHash> &Track,
                std::unordered_set<Position, PositionHash> &Walls,
                Position &Start, Position &End, int32_t &Rows, int32_t &Cols) {
  std::stringstream ss((std::string(Input)));
  std::string line{};
  char square;
  int32_t row = 0;
  int32_t col = 0;

  while (getline(ss, line, '\n')) {
    col = 0;
    std::stringstream ss2(line);
    while (ss2 >> square) {
      switch (square) {
      case '#':
        Walls.insert(Position{row, col});
        break;
      case 'S':
        Start = Position{row, col};
        Track.insert(std::make_pair(Start, Info{0, false, track}));
        break;
      case 'E':
        End = Position{row, col};
        Track.insert(std::make_pair(End, Info{INT64_MAX, false, track}));
        break;
      case '.':
        Track.insert(
            std::make_pair(Position{row, col}, Info{INT64_MAX, false, track}));
        break;
      default:
        break;
      }
      col++;
    }
    row++;
  }
  Cols = col;
  Rows = row;
}

int64_t trackTime(std::unordered_map<Position, Info, PositionHash> &Track,
                  Position Start, Position End, int32_t Rows, int32_t Cols,
                  std::unordered_set<Position, PositionHash> &Route,
                  bool GetRoute) {
  int64_t trackTime = INT64_MAX;
  std::vector<Position> q{Start};
  bool cheat1Visited = false;
  while (!q.empty()) {
    Position pos = q.back();
    q.pop_back();
    for (auto const &dir : directions) {
      Position newPos = pos + dir;
      if (Track[pos].type == cheat1) {
        if (!Track.contains(newPos) || Track[newPos].type != cheat2) {
          continue;
        }
        cheat1Visited = true;
      }
      if (Track[pos].type == cheat2 && !cheat1Visited) {
        continue;
      }
      if (newPos.col == 0 || newPos.row == 0 || newPos.col == Cols - 1 ||
          newPos.row == Rows - 1) {
        continue;
      }
      if (Track.contains(newPos)) {
        if (Track[newPos].time > Track[pos].time + 1) {
          Track[newPos].time = Track[pos].time + 1;
          if (newPos == End) {
            trackTime = Track[End].time;
            continue;
          }
          if (!Track[newPos].visited) {
            q.push_back(newPos);
          }
        }
      }
    }
  }
  if (GetRoute) {
    std::unordered_map<Position, Position, PositionHash> possibleRoutes;
    possibleRoutes.insert(std::make_pair(End, Position{-1, -1}));
    std::vector<Position> q2{End};
    while (!q2.empty()) {
      Position pos = q2.back();
      q2.pop_back();
      for (auto const &dir : directions) {
        if (Track.contains(pos + dir) &&
            Track[pos + dir].time == Track[pos].time - 1) {
          possibleRoutes.insert(std::make_pair(pos + dir, pos));
          q2.push_back(pos + dir);
        }
      }
    }
    Position pos = Start;
    while (pos != End) {
      Route.insert(pos);
      if (possibleRoutes.contains(pos)) {
        pos = possibleRoutes[pos];
      } else {
        break;
      }
    }
    Route.insert(End);
  }
  if (trackTime < INT64_MAX / 2) {
    return trackTime;
  } else {
    return INT64_MAX / 2;
  }
}

uint64_t result(const std::string_view input) {

  std::unordered_set<Position, PositionHash> walls{};
  Position start;
  Position end;
  std::unordered_map<Position, Info, PositionHash> track{};
  int32_t rows;
  int32_t cols;
  uint64_t cheatCount = 0;
  std::unordered_set<Position, PositionHash> route{};

  ParseInput(input, track, walls, start, end, rows, cols);
  int64_t noCheatTime = trackTime(track, start, end, rows, cols, route, true);

  for (auto const &step : route) {
    for (auto const &other : route) {
      uint64_t cheatDistance =
          abs(step.col - other.col) + abs(step.row - other.row);
      int64_t cheatTime = track[other].time - track[step].time - cheatDistance;
      if (cheatDistance <= 20 && cheatTime >= 100) {

        cheatCount++;
        /*  std::cout << "row " << std::setw(3) << step.row << ", col "
                   << std::setw(3) << step.col << ", endrow " << std::setw(3)
                   << other.row << ", endcol " << std::setw(3) << other.col
                   << ", cheat time " << std::setw(6) << cheatTime
                   << ", cheat distance " << std::setw(6) << cheatDistance
                   << ", cheat count " << std::setw(6) << cheatCount
                   << std::endl; */
      }
    }
  }
  return cheatCount; // example = 285
}
} // namespace part_two