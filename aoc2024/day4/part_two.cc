module;
#include <regex>
#include <string_view>

export module part_two;

export namespace part_two {
uint64_t result(const std::string_view input) {
  std::string text(input);
  std::vector<std::vector<char>> wordsearch;
  std::stringstream ss((std::string(input)));
  std::string row;

  while (std::getline(ss, row, '\n')) {
    std::vector<char> rowData;
    std::stringstream rowStream(row);
    char value;

    while (rowStream >> value) {
      rowData.push_back(value);
    }

    wordsearch.push_back(rowData);
  }

  uint64_t count = 0;
  for (int32_t row = 1; row < wordsearch.size() - 1; row++) {
    for (int32_t col = 1; col < wordsearch[0].size() - 1; col++) {
      if (wordsearch[row][col] == 'A') {
        //.M.M.
        //..A..
        //.S.S.
        if ((wordsearch[row - 1][col - 1] == 'M') &&
            (wordsearch[row - 1][col + 1] == 'M') &&
            (wordsearch[row + 1][col - 1] == 'S') &&
            (wordsearch[row + 1][col + 1] == 'S')) {
          count++;
        }
        //.M.S.
        //..A..
        //.M.S.
        else if ((wordsearch[row - 1][col - 1] == 'M') &&
                 (wordsearch[row + 1][col - 1] == 'M') &&
                 (wordsearch[row - 1][col + 1] == 'S') &&
                 (wordsearch[row + 1][col + 1] == 'S')) {
          count++;
        }
        //.S.S.
        //..A..
        //.M.M.
        else if ((wordsearch[row + 1][col - 1] == 'M') &&
                 (wordsearch[row + 1][col + 1] == 'M') &&
                 (wordsearch[row - 1][col - 1] == 'S') &&
                 (wordsearch[row - 1][col + 1] == 'S')) {
          count++;
        }
        //.S.M.
        //..A..
        //.S.M.
        else if ((wordsearch[row - 1][col + 1] == 'M') &&
                 (wordsearch[row + 1][col + 1] == 'M') &&
                 (wordsearch[row - 1][col - 1] == 'S') &&
                 (wordsearch[row + 1][col - 1] == 'S')) {
          count++;
        }
      }
    }
  }
  return count;
}
} // namespace part_two