#include <atomic>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "pool.hpp"

#include "dirstat.hpp"

int main() {
  std::atomic_uint64_t total_line_count = 0;
  std::atomic_uint64_t total_word_count = 0;
  std::atomic_uint64_t total_char_count = 0;
  const auto cur_path = std::filesystem::current_path();
  std::uint32_t file_count = 0;
  {
    dirstat::Pool pool;
    for (auto const &dir_entry :
         std::filesystem::recursive_directory_iterator{cur_path}) {
      if (!dir_entry.is_regular_file())
        continue;

      pool.push_job(std::bind(&dirstat::process_file, dir_entry.path(),
                              &total_line_count, &total_word_count,
                              &total_char_count));
      ++file_count;
    }
  }
  std::cout << "File count: " << file_count << std::endl;
  std::cout << "Line count: " << total_line_count.load() << std::endl;
  std::cout << "Word count: " << total_word_count.load() << std::endl;
  std::cout << "Char count: " << total_char_count.load() << std::endl;
}

