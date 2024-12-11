module;
#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

export module part_two;

export namespace part_two {

using namespace std;

bool isCycle(vector<vector<char>> grid, int si, int sj, int sdir, int oi,
             int oj) {
  int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  int ci = si, cj = sj, dir = sdir;
  vector<vector<int>> dirc(grid.size(), vector<int>(grid.at(0).size(), -1));
  do {
    ci += dirs[dir][0], cj += dirs[dir][1];
    if (ci >= 0 && ci < grid.size() && cj >= 0 && cj < grid.at(ci).size()) {
      if (dirc.at(ci).at(cj) == dir) {
        return true;
      } else {
        dirc.at(ci).at(cj) = dir;
      }
      if (grid.at(ci).at(cj) == '#' || (ci == oi && cj == oj)) {
        ci -= dirs[dir][0], cj -= dirs[dir][1];
        dir = (dir + 1) % 4;
      }
    }
  } while (ci >= 0 && ci < grid.size() && cj >= 0 && cj < grid.at(ci).size());
  return false;
}

int part1(vector<vector<char>> grid) {
  int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  int result = 0, ci = 0, cj = 0, dir = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid.at(i).size(); j++) {
      if (grid.at(i).at(j) == '^') {
        ci = i, cj = j;
        break;
      }
    }
  }
  do {
    if (grid.at(ci).at(cj) != 'X') {
      grid.at(ci).at(cj) = 'X';
      result++;
    }
    ci += dirs[dir][0], cj += dirs[dir][1];
    if (ci >= 0 && ci < grid.size() && cj >= 0 && cj < grid.at(ci).size() &&
        grid.at(ci).at(cj) == '#') {
      ci -= dirs[dir][0], cj -= dirs[dir][1];
      dir = (dir + 1) % 4;
    }
  } while (ci >= 0 && ci < grid.size() && cj >= 0 && cj < grid.at(ci).size());
  return result;
}

int result(std::string_view sv) {
  vector<vector<char>> grid;
  std::stringstream ss((std::string(sv)));
  std::string row;

  while (std::getline(ss, row, '\n')) {

    std::stringstream rowStream(row);
    char square;
    std::vector<char> mapRow;

    for (uint32_t j = 0; j < row.size(); j++) {
      rowStream >> square;
      mapRow.push_back(square);
    }
    grid.push_back(mapRow);
  }
  int result = 0, ci = 0, cj = 0, dir = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid.at(i).size(); j++) {
      if (grid.at(i).at(j) == '^') {
        ci = i, cj = j;
        break;
      }
    }
  }
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid.at(i).size(); j++) {
      if (i == ci && j == cj) {
        continue;
      }
      auto testGrid(grid);
      if (isCycle(testGrid, ci, cj, dir, i, j)) {
        result++;
      }
    }
  }
  return result;
}
} // namespace part_two
