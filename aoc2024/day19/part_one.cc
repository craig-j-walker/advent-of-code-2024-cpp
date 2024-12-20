module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <map>
#include <set>
#include <sstream>
#include <string_view>
#include <sys/types.h>
#include <vector>

export module part_one;

export namespace part_one {

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
  uint64_t count = 0;
  std::map<std::string, bool> memos;
  std::vector<std::string> queue;

  while (getline(ss, line, '\n')) {
    queue.clear();
    queue.push_back(line);
    bool found = false;
    memos.clear();
    while (!queue.empty() && !found) {
      std::string memo = queue.back();
      queue.pop_back();
      for (auto const &token : tokens) {
        std::string subMemo = "?";
        if (memo.length() >= token.length()) {
          subMemo = memo.substr(token.length());
        }
        if (memos.contains(subMemo)) {
          memos.insert(std::make_pair(memo, memos[subMemo]));
        } else if (memo == token) {
          found = true;
          break;
        } else if (memo.starts_with(token)) {
          subMemo = memo.substr(token.length());
          queue.push_back(subMemo);
        } else {
          memos.insert(std::make_pair(memo, false));
        }
      }
    }
    if (found) {

      count++;
    }
  }
  return count;
}

} // namespace part_one