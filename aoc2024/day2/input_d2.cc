module;

#include <filesystem>
#include <fstream>
#include <string_view>

export module input_d2;

export namespace input_d2 {
const std::string_view input_d2() {
  const std::string &inputPath =
      std::filesystem::current_path() / "input_file_d2.txt";
  std::ifstream file(inputPath);
  if (!file.is_open()) {
    throw std::runtime_error("Could not find: " + inputPath);
  }

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());

  const std::string_view contentView(content);

  return contentView;
}
} // namespace input_d2