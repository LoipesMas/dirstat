#include <atomic>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "pool.hpp"

#include "dirstat.hpp"

int main(int argc, char *argv[]) {
  // Use current path by default
  auto path = std::filesystem::current_path();

  // Handle arguments
  if (argc > 2) {
    std::cout << "Too many arguments" << std::endl;
    return 1;
  } else if (argc == 2) {
    path = std::filesystem::path(argv[1]);
    if (!std::filesystem::exists(path)) {
      std::cout << "Invalid path" << std::endl;
      return 2;
    }
  }

  dirstat::Counts counts;
  counts.file_count = 0;
  counts.line_count = 0;
  counts.word_count = 0;
  counts.char_count = 0;

  dirstat::run_in_path(path, &counts);

  std::cout << "File count: " << counts.file_count << std::endl;
  std::cout << "Line count: " << counts.line_count << std::endl;
  std::cout << "Word count: " << counts.word_count << std::endl;
  std::cout << "Char count: " << counts.char_count << std::endl;
}
