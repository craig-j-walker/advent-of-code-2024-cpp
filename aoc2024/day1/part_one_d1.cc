module;
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string_view>
#include <system_error>
#include <vector>

export module part_one_d1;

export namespace part_one_d1 {
int64_t sum_distance(const std::string_view instructions) {

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

  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  auto it1 = list1.begin();
  auto it2 = list2.begin();

  num = 0;

  while (it1 != list1.end() && it2 != list2.end()) {
    int64_t dist = *it1 - *it2;
    num += std::abs(dist);
    it1 = std::next(it1);
    it2 = std::next(it2);
  }

  return num;
}
} // namespace part_one_d1