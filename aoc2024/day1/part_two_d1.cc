module;
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string_view>
#include <system_error>
#include <vector>

export module part_two_d1;

export namespace part_two_d1 {
int64_t sum_similarity(const std::string_view instructions) {

  std::vector<std::string_view> tokens;
  std::vector<int64_t> list1;
  std::vector<int64_t> list2;
  int64_t num;
  char delimiter = ' ';
  size_t first = 0;

  while (first < instructions.size()) {
    const auto second = instructions.find_first_of(delimiter, first);

    if (first != second) {
      tokens.emplace_back(instructions.substr(first, second - first));
    }
    if (second == std::string_view::npos) {
      return -1;
    }
    first = second + 1;
  }

  int i = 0;
  for (auto &token : tokens) {
    auto [ptr, ec] =
        std::from_chars(token.data(), token.data() + token.size(), num);
    if (ec == std::errc()) {
      if (i % 2 == 0) {
        list1.push_back(num);
      } else {
        list2.push_back(num);
      }
      i++;
    } else {
      std::cout << "Conversion failed" << std::endl;
      return -2;
    }
  }

  auto it1 = list1.begin();

  num = 0;

  while (it1 != list1.end()) {
    int64_t similarity = *it1 * std::count(list2.begin(), list2.end(), *it1);
    num += similarity;
    it1 = std::next(it1);
  }

  return num;
}
} // namespace part_two_d1