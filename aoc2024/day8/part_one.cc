module;
#include <cstdint>
#include <iostream>
#include <regex>
#include <set>
#include <string_view>
#include <sys/types.h>

export module part_one;

export namespace part_one {

struct Antenna {
public:
  int32_t row;
  int32_t col;
  char frequency;

  // compare for match
  bool operator==(const Antenna &pt) const {
    return (row == pt.row && col == pt.row);
  }
};

struct Antinode {
public:
  int32_t row;
  int32_t col;
  // compare for order.
  bool operator<(const Antinode &pt) const {
    return (row < pt.row) || ((!(pt.row < row)) && (col < pt.col));
  }
};

void FindAntinodes(std::vector<Antenna> antennae, std::set<Antinode> &antinodes,
                   int rows, int cols) {
  int nAntennae = antennae.size();
  for (int i = 0; i < nAntennae; i++) {
    Antenna antenna = antennae.back();
    antennae.pop_back();
    for (auto &other : antennae) {
      if (antenna.frequency == other.frequency) {
        int32_t vert = antenna.row - other.row;
        int32_t hor = antenna.col - other.col;
        Antinode antinode{antenna.row + vert, antenna.col + hor};
        if (antinode.col >= 0 && antinode.col < cols && antinode.row >= 0 &&
            antinode.row < rows) {
          antinodes.insert(antinode);
        }
        antinode = Antinode{other.row - vert, other.col - hor};
        if (antinode.col >= 0 && antinode.col < cols && antinode.row >= 0 &&
            antinode.row < rows) {
          antinodes.insert(antinode);
        }
      }
    }
  }
}
uint64_t result(const std::string_view input) {
  std::vector<Antenna> antennae;
  std::string line;
  std::stringstream ss((std::string(input)));
  std::set<Antinode> antinodes;

  int32_t finalRow = 0;
  int32_t finalCol = 0;
  while (std::getline(ss, line)) {
    std::vector<char> squares(line.begin(), line.end());
    finalCol = 0;
    for (auto &square : squares) {
      if (square != '.') {
        antennae.push_back(Antenna{finalRow, finalCol, square});
      }
      finalCol++;
    }
    finalRow++;
  }

  FindAntinodes(antennae, antinodes, finalRow, finalCol);

  /* for (int i = 0; i <= finalRow; i++) {
    for (int j = 0; j <= finalCol; j++) {
      for (auto const &antenna : antennae) {
        if (antenna.row == i && antenna.col == j) {
          std::cout << antenna.frequency;
          break;
        }
      }
      if (antinodes.contains(Antinode{i, j})) {
        std::cout << '#';
      } else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  } */
  return antinodes.size();
}
} // namespace part_one