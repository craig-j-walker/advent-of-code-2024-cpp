import example;
import input;
import part_one;
import part_two;

#include <cstdint>
#include <iostream>

int main() {
  // uint64_t result = part_one::result(input::input);
  uint64_t result = part_one::result(example::example);
  if (result > 0) {
    std::cout << "Part 1 result: " << result << "\n";
  } else {
    std::cout << "An error occurred in part 1."
              << "\n";
    return -1;
  }
  result = part_two::result(input::input);
  // result = part_two::result(example::example);
  if (result > 0) {
    std::cout << "Part 2 result: " << result << "\n";
    return 0;
  } else {
    std::cout << "An error occurred in part 2."
              << "\n";
    return -1;
  }
}