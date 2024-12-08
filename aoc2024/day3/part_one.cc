module;
#include <regex>
#include <string_view>

export module part_one;

export namespace part_one {
uint64_t result(const std::string_view input) {
  std::string text(input);
  std::regex pattern("(mul\\(\\d{1,3},\\d{1,3}\\))");
  std::regex numberPattern("(\\d{1,3})");
  auto begin = std::sregex_iterator(text.begin(), text.end(), pattern);
  auto end = std::sregex_iterator();
  uint64_t total = 0;
  for (auto it = begin; it != end; ++it) {
    std::smatch match = *it;
    std::string matchstr = match.str();
    auto itNum = std::sregex_iterator(match.str().begin(), match.str().end(),
                                      numberPattern);
    std::smatch matchNum = *itNum;
    uint64_t num1 = std::atof(matchNum.str().c_str());
    ++itNum;
    matchNum = *itNum;
    uint64_t num2 = std::atof(matchNum.str().c_str());
    uint64_t mul = num1 * num2;
    total += mul;
  }
  return total;
}
} // namespace part_one