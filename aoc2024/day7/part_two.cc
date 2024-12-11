
module;
#include <regex>
#include <string>
#include <string_view>

export module part_two;

export namespace part_two {
uint64_t result(const std::string_view input) {
  uint64_t result = 0;

  std::vector<std::tuple<int64_t, std::vector<int64_t>>> equations;
  std::string row;
  std::stringstream ss((std::string(input)));

  while (std::getline(ss, row, '\n')) {

    std::stringstream rowStream(row);
    int64_t testValue;
    rowStream >> testValue;
    char colon;
    rowStream >> colon;
    std::vector<int64_t> variables;
    int64_t variable;
    std::string item;
    while (std::getline(rowStream, item, ' ')) {
      if (item != "") {
        variable = stoi(item);
        variables.push_back(variable);
      }
    }
    std::tuple<int64_t, std::vector<int64_t>> equation{testValue, variables};
    equations.push_back(equation);
  }

  for (auto &equation : equations) {
    int64_t testValue = std::get<0>(equation);
    std::vector<int64_t> variables = std::get<1>(equation);
    std::vector<int64_t> answers{0};
    std::vector<int64_t> oldAnswers;
    std::vector<char> ops{'+', '*', '|'};
    std::string s1;
    std::string s2;

    for (auto &variable : variables) {
      oldAnswers = answers;
      answers.clear();
      for (auto &oldAnswer : oldAnswers) {
        for (auto &op : ops) {
          if (op == '+') {
            answers.push_back(oldAnswer + variable);
          } else if (op == '*') {
            answers.push_back(oldAnswer * variable);
          } else if (op == '|') {
            s1 = std::to_string(oldAnswer);
            s2 = std::to_string(variable);
            answers.push_back(stoll(s1 + s2));
          }
        }
      }
    }
    for (auto answer : answers) {
      if (answer == testValue) {
        result += testValue;
        break;
      }
    }
  }
  return result;
}
} // namespace part_two