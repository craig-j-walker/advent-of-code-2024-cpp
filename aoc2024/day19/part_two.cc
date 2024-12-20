
module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <utility>
#include <vector>

export module part_two;

export namespace part_two {

uint64_t Search(std::string Memo, std::map<std::string, uint64_t> &Memos,
                const std::set<std::string> &Tokens) {
  if (Memos.contains(Memo)) {
    return Memos[Memo];
  }
  uint64_t sum = 0;
  for (auto const &t : Tokens) {
    if (Memo == t) {
      sum += 1;
    } else if (Memo.starts_with(t)) {
      sum += Search(Memo.substr(t.length()), Memos, Tokens);
    }
  }
  Memos.insert(std::make_pair(Memo, sum));

  return sum;
}

uint64_t result(const std::string_view input) {
  std::stringstream ss((std::string(input)));
  std::string line{};

  getline(ss, line, '\n');

  std::stringstream ss2(line);
  std::set<std::string> tokens;

  while (getline(ss2, line, ',')) {
    if (line.substr(0, 1) == " ") {
      line = line.substr(1);
    }
    tokens.insert(line);
  }

  getline(ss, line, '\n');
  uint64_t sum = 0;
  std::map<std::string, uint64_t> memos;
  std::vector<std::string> queue;

  while (getline(ss, line, '\n')) {
    memos.clear();
    // std::cout << line << std::endl;
    uint64_t result = Search(line, memos, tokens);
    // std::cout << result << std::endl;
    sum += result;
  }
  return sum;
}

} // namespace part_two