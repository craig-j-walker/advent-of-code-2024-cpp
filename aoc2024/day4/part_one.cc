module;
#include <regex>
#include <string_view>

export module part_one;

export namespace part_one {
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
  std::vector<char> word{'X', 'M', 'A', 'S'};
  for (int32_t row = 0; row < wordsearch.size(); row++) {
    for (int32_t col = 0; col < wordsearch[0].size(); col++) {
      bool found = true;
      // down
      for (int32_t k = 0; k < word.size(); k++) {
        if (row + k < wordsearch.size()) {
          if (wordsearch[row + k][col] == word[k]) {
            continue;
          } else {
            found = false;
            break;
          }
        } else {
          found = false;
          break;
        }
      }
      if (found) {
        count++;
      }
      // up
      found = true;
      for (int32_t k = 0; k < word.size(); k++) {
        if (row - k >= 0) {
          if (wordsearch[row - k][col] == word[k]) {
            continue;
          } else {
            found = false;
            break;
          }
        } else {
          found = false;
          break;
        }
      }
      if (found) {
        count++;
      }
      // right
      found = true;
      for (int32_t k = 0; k < word.size(); k++) {
        if (col + k < wordsearch[0].size()) {
          if (wordsearch[row][col + k] == word[k]) {
            continue;
          } else {
            found = false;
            break;
          }
        } else {
          found = false;
          break;
        }
      }
      if (found) {
        count++;
      }
      // left
      found = true;
      for (int32_t k = 0; k < word.size(); k++) {
        if (col - k >= 0) {
          if (wordsearch[row][col - k] == word[k]) {
            continue;
          } else {
            found = false;
            break;
          }
        } else {
          found = false;
          break;
        }
      }
      if (found) {
        count++;
      }
      // down+right
      found = true;
      for (int32_t k = 0; k < word.size(); k++) {
        if ((row + k < wordsearch.size()) && (col + k < wordsearch[0].size())) {
          if (wordsearch[row + k][col + k] == word[k]) {
            continue;
          } else {
            found = false;
            break;
          }
        } else {
          found = false;
          break;
        }
      }
      if (found) {
        count++;
      }
      // down+left
      found = true;
      for (int32_t k = 0; k < word.size(); k++) {
        if ((row + k < wordsearch.size()) && (col - k >= 0)) {
          if (wordsearch[row + k][col - k] == word[k]) {
            continue;
          } else {
            found = false;
            break;
          }
        } else {
          found = false;
          break;
        }
      }
      if (found) {
        count++;
      }
      // up+right
      found = true;
      for (int32_t k = 0; k < word.size(); k++) {
        if ((row - k >= 0) && (col + k < wordsearch[0].size())) {
          if (wordsearch[row - k][col + k] == word[k]) {
            continue;
          } else {
            found = false;
            break;
          }
        } else {
          found = false;
          break;
        }
      }
      if (found) {
        count++;
      }
      // up+left
      found = true;
      for (int32_t k = 0; k < word.size(); k++) {
        if ((row - k >= 0) && (col - k >= 0)) {
          if (wordsearch[row - k][col - k] == word[k]) {
            continue;
          } else {
            found = false;
            break;
          }
        } else {
          found = false;
          break;
        }
      }
      if (found) {
        count++;
      }
    }
  }
  return count;
}
} // namespace part_one