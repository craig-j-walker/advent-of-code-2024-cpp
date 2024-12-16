
module;
#include <cstdint>
#include <limits>
#include <map>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_one;

export namespace part_one {

int steps = 100;
int cols = 101;
int rows = 103;

// int cols = 11;
// int rows = 7;

int q1 = 0;
int q2 = 0;
int q3 = 0;
int q4 = 0;
uint64_t safetyFactor = 0;
int stepsCol;
int stepsRow;

uint64_t result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};

  while (getline(ss, line, '\n')) {
    std::stringstream ss2(line);
    char blurb;
    ss2 >> blurb;
    ss2 >> blurb;
    int col;
    ss2 >> col;
    ss2 >> blurb;
    int row;
    ss2 >> row;
    ss2 >> blurb;
    ss2 >> blurb;
    int vcol;
    ss2 >> vcol;
    ss2 >> blurb;
    int vrow;
    ss2 >> vrow;

    if (vcol > 0) {
      stepsCol = (col + (vcol * steps)) % cols;
    } else {
      stepsCol = (cols - (cols - col + (-vcol * steps)) % cols) % cols;
    }
    if (vrow > 0) {
      stepsRow = (row + (vrow * steps)) % rows;
    } else {
      stepsRow = (rows - (rows - row + (-vrow * steps)) % rows) % rows;
    }
    if (stepsCol < cols / 2 && stepsRow < rows / 2) {
      q1++;
    }
    if (stepsCol > cols / 2 && stepsRow < rows / 2) {
      q2++;
    }
    if (stepsCol < cols / 2 && stepsRow > rows / 2) {
      q3++;
    }
    if (stepsCol > cols / 2 && stepsRow > rows / 2) {
      q4++;
    }
  }
  safetyFactor = q1 * q2 * q3 * q4;
  return safetyFactor;
}
} // namespace part_one