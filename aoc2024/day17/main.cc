import example;
import input;
import part_one;
import part_two;
#include <chrono>
#include <cstdint>
#include <iostream>
#include <locale>

int main() {
  std::string p1Result;
  uint64_t p2Result;
  auto p1Start = std::chrono::high_resolution_clock::now();
  p1Result = part_one::result(input::input);
  // p1Result = part_one::result(example::example);
  auto p1End = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> p1Duration = p1End - p1Start;

  if (p1Result != "") {
    std::cout << "Part 1 result: " << p1Result
              << ", took: " << p1Duration.count() << " milliseconds"
              << std::endl;
  } else {
    std::cout << "An error occurred in part 1."
              << "\n";
    return -1;
  }
  auto p2Start = std::chrono::high_resolution_clock::now();
  p2Result = part_two::result(input::input);
  //  p2Result = part_two::result(example::example);
  auto p2End = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> p2Duration = p2End - p2Start;

  if (p2Result > 0) {
    std::cout << "Part 2 result: " << p2Result
              << ", took: " << p2Duration.count() << " milliseconds"
              << std::endl;
    return 0;
  } else {
    std::cout << "An error occurred in part 2."
              << "\n";
    return -1;
  }
}