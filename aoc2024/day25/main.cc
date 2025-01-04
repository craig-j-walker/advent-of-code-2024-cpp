import example;
import input;
import part_one;
import part_two;
#include <chrono>
#include <iostream>

int main() {
  auto p1Start = std::chrono::high_resolution_clock::now();
  auto p1Result = part_one::result(input::input);
  // auto p1Result = part_one::result(example::example);
  auto p1End = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> p1Duration = p1End - p1Start;

  if (p1Result != 0) {
    std::cout << "Part 1 result: " << p1Result
              << ", took: " << p1Duration.count() << " milliseconds"
              << std::endl;
  } else {
    std::cout << "An error occurred in part 1."
              << "\n";
    // return -1;
  }
  auto p2Start = std::chrono::high_resolution_clock::now();
  auto p2Result = part_two::result(input::input);
  // auto p2Result = part_two::result(example::example);
  auto p2End = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> p2Duration = p2End - p2Start;

  if (p2Result != "") {
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