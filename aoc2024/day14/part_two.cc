
module;
#include <cmath>
#include <cstdint>
#include <iostream>
#include <set>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_two;

export namespace part_two {

int cols = 101;
int rows = 103;
int stepsCol;
int stepsRow;

struct RobotType {
  int col0;
  int row0;
  int vCol;
  int vRow;
  int col;
  int row;
};
std::set<std::pair<int, int>> positions{};
uint64_t result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};
  std::vector<RobotType> robots;
  while (getline(ss, line, '\n')) {
    std::stringstream ss2(line);
    RobotType robot;
    char blurb;
    ss2 >> blurb;
    ss2 >> blurb;
    ss2 >> robot.col0;
    ss2 >> blurb;
    ss2 >> robot.row0;
    ss2 >> blurb;
    ss2 >> blurb;
    ss2 >> robot.vCol;
    ss2 >> blurb;
    ss2 >> robot.vRow;
    robots.push_back(robot);
  }

  float vert = 30;
  float hor = 81;

  float nhor = 0;
  float nvert = 0;

  float vertgrad = static_cast<float>(cols) / static_cast<float>(rows);
  float vertoffset = (hor - vert) / static_cast<float>(rows);

  while (nvert == 0 || std::remainder(nvert, 1.0) != 0) {
    nhor++;
    nvert = vertoffset + nhor * vertgrad;
  }

  uint64_t steps = vert + nvert * rows;

  positions.clear();
  for (auto &robot : robots) {
    if (robot.vCol > 0) {
      robot.col = (robot.col0 + (robot.vCol * steps)) % cols;
    } else {
      robot.col =
          (cols - (cols - robot.col0 + (-robot.vCol * steps)) % cols) % cols;
    }
    if (robot.vRow > 0) {
      robot.row = (robot.row0 + (robot.vRow * steps)) % rows;
    } else {
      robot.row =
          (rows - (rows - robot.row0 + (-robot.vRow * steps)) % rows) % rows;
    }
    positions.insert(std::pair<int, int>{robot.col, robot.row});
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::pair<int, int> position{j, i};
      if (positions.contains(position)) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "----------------------------------------------" << std::endl;
  std::cout << steps << std::endl;
  std::cout << "----------------------------------------------" << std::endl;

  return 1;
}

} // namespace part_two