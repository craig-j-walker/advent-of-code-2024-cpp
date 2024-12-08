module;
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string_view>
#include <system_error>
#include <vector>

export module part_one_d2;

export namespace part_one_d2 {
int64_t safe(const std::string_view input) {

  std::vector<std::string_view> reportTokens;
  std::vector<std::string_view> reports;
  int64_t num;
  int64_t prevNum;
  int64_t dir;
  int64_t prevDir;
  int64_t numSafe = 0;
  bool safe;
  char reportDelimiter = '\n';
  char delimiter = ' ';
  size_t first = 0;

  while (first < input.size()) {
    const auto second = input.find_first_of(reportDelimiter, first);

    if (first != second) {
      reports.emplace_back(input.substr(first, second - first));
    }
    if (second == std::string_view::npos) {
      break;
    }
    first = second + 1;
  }

  for (auto &report : reports) {
    first = 0;
    reportTokens.clear();
    while (first < report.size()) {
      const auto second = report.find_first_of(delimiter, first);
      if (first != second) {
        reportTokens.emplace_back(report.substr(first, second - first));
      }
      if (second == std::string_view::npos) {
        break;
      }
      first = second + 1;
    }

    int i = 0;
    for (auto &token : reportTokens) {
      auto [ptr, ec] =
          std::from_chars(token.data(), token.data() + token.size(), num);
      if (ec == std::errc()) {
        int64_t diff = num - prevNum;
        if (i == 0) {
          safe = true;
        } else {
          if (diff < 0 && diff > -4) {
            dir = -1;
          } else if (diff > 0 && diff < 4) {
            dir = 1;
          } else {
            safe = false;
            break;
          }
          if (i == 1) {
            safe = true;
          } else {
            if (prevDir == dir) {
              safe = true;
            } else {
              safe = false;
              break;
            }
          }
        }
        prevNum = num;
        prevDir = dir;

      } else {
        std::cout << "Conversion failed" << std::endl;
        return -2;
      }
      i++;
    }
    if (safe == true) {
      numSafe++;
    }
  }
  return numSafe;
}
} // namespace part_one_d2