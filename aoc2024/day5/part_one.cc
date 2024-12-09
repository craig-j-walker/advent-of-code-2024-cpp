module;
#include <regex>
#include <string_view>

export module part_one;

export namespace part_one {
uint64_t result(const std::string_view input) {
  uint64_t answer = 0;
  std::vector<std::tuple<int32_t, int32_t>> rules;
  std::vector<std::vector<int32_t>> updates;
  std::string row;
  std::stringstream ss((std::string(input)));
  bool inRules = true;

  while (std::getline(ss, row, '\n')) {

    std::stringstream rowStream(row);

    if (row == "") {

      inRules = false;

    } else if (inRules) {

      int32_t left;
      char bar;
      int32_t right;

      rowStream >> left;
      rowStream >> bar;
      rowStream >> right;
      rules.push_back(std::tuple<int32_t, int32_t>(left, right));

    } else {
      std::string item;
      int32_t value;
      std::vector<int32_t> update;

      while (std::getline(rowStream, item, ',')) {
        value = stoi(item);
        update.push_back(value);
      }
      updates.push_back(update);
    }
  }

  for (auto &update : updates) {
    int i = 0;
    bool ruleBreak = false;
    for (auto &page : update) {
      for (auto &rule : rules) {
        int32_t left = std::get<0>(rule);
        int32_t right = std::get<1>(rule);
        if (page == left) {
          for (int32_t j = i - 1; j >= 0; j--) {
            if (right == update[j]) {
              ruleBreak = true;
              break;
            }
          }
          if (ruleBreak) {
            break;
          }
        } else if (page == right) {
          for (int32_t j = i + 1; j < update.size(); j++) {
            if (left == update[j]) {
              ruleBreak = true;
              break;
            }
          }
          if (ruleBreak) {
            break;
          }
        }
        if (ruleBreak) {
          break;
        }
      }
      if (ruleBreak) {
        break;
      }
      i++;
    }
    if (!ruleBreak) {
      int32_t middle = update.size() / 2;
      int64_t updateResult = update[middle];
      answer += updateResult;
    }
  }
  return answer;
}
} // namespace part_one