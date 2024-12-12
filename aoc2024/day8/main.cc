import example;
import input;
import part_one;
import part_two;

#include <chrono>
#include <cstdint>
#include <iostream>

int main() {
  uint64_t result;
  auto p1Start = std::chrono::high_resolution_clock::now();
  result = part_one::result(input::input);
  // result = part_one::result(example::example);
  auto p1End = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> p1Duration = p1End - p1Start;

  if (result > 0) {
    std::cout << "Part 1 result: " << result << ", took: " << p1Duration.count()
              << " milliseconds" << std::endl;
  } else {
    std::cout << "An error occurred in part 1."
              << "\n";
    return -1;
  }
  auto p2Start = std::chrono::high_resolution_clock::now();
  result = part_two::result(input::input);
  // result = part_two::result(example::example);
  auto p2End = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> p2Duration = p2End - p2Start;

  if (result > 0) {
    std::cout << "Part 2 result: " << result << ", took: " << p2Duration.count()
              << " milliseconds" << std::endl;
    return 0;
  } else {
    std::cout << "An error occurred in part 2."
              << "\n";
    return -1;
  }
}