import example_d2;
import input_d2;
import part_one_d2;
import part_two_d2;

#include <iostream>

int main() {
  int64_t result = part_one_d2::sum_distance(input_d2::input_d2());
  if (result > 0) {
    std::cout << "The total distance is: " << result << "\n";
  } else {
    std::cout << "an error occurred in part 1."
              << "\n";
    return -1;
  }
  result = part_two_d2::sum_similarity(input_d2::input_d2());
  if (result > 0) {
    std::cout << "The total similarity is: " << result << "\n";
    return 0;
  } else {
    std::cout << "an error occurred in part 2."
              << "\n";
    return -1;
  }
}