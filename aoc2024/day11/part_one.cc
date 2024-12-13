
module;
#include <cstdint>
#include <math.h>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unordered_map>
#include <utility>

export module part_one;

export namespace part_one {

int num_digits(std::int64_t x) { return static_cast<int>(log10(x)) + 1; }

uint64_t result(const std::string_view input) {
  int steps = 25;
  std::unordered_map<std::int64_t, std::int64_t> curr, next;
  std::stringstream ss;
  ss << std::string(input);
  uint64_t val;
  while (ss >> val) {
    curr.insert({val, 1});
  }

  while (steps-- > 0) {
    for (auto const [stone_val, count] : curr) {
      if (stone_val == 0) {
        next[1] += count;
      } else if (int d = num_digits(stone_val); !(d & 1)) {
        std::int64_t const half_pow = std::pow(10, d / 2);
        std::int64_t const l = stone_val / half_pow;
        std::int64_t const r = stone_val - (l * half_pow);
        next[l] += count;
        next[r] += count;
      } else {
        next[2024 * stone_val] += count;
      }
    }
    curr.swap(next);
    next.clear();
  }
  uint64_t size = 0;
  for (auto &stone : curr) {
    size += stone.second;
  }
  return size;
}

} // namespace part_one