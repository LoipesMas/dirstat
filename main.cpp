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
  std::uint64_t file_count = 0;
  std::atomic_uint64_t total_line_count = 0;
  std::atomic_uint64_t total_word_count = 0;
  std::atomic_uint64_t total_char_count = 0;

  dirstat::run_in_path(path, &file_count, &total_line_count, &total_word_count,
                       &total_char_count);

  std::cout << "File count: " << file_count << std::endl;
  std::cout << "Line count: " << total_line_count.load() << std::endl;
  std::cout << "Word count: " << total_word_count.load() << std::endl;
  std::cout << "Char count: " << total_char_count.load() << std::endl;
}
