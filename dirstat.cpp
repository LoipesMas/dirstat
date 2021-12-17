#include "dirstat.hpp"
#include "pool.hpp"

namespace dirstat {
void process_file(std::filesystem::path file_path,
                  std::atomic_uint64_t *total_line_count,
                  std::atomic_uint64_t *total_word_count,
                  std::atomic_uint64_t *total_char_count) {
  std::fstream file;
  file.open(file_path.string(), std::ios::in);
  std::string line;
  std::uint32_t line_count = 0;
  std::uint64_t word_count = 0;
  std::uint64_t char_count = 0;

  bool prev_space = false;

  while (std::getline(file, line)) {
    if (!line.empty())
      ++word_count;
    for (auto c : line) {
      ++char_count;
      if (c == ' ' && !prev_space)
        ++word_count;
      prev_space = c == ' ';
    }
    ++line_count;
  }

  file.close();
  *total_line_count += line_count;
  *total_word_count += word_count;
  *total_char_count += char_count;
}

void run_in_path(std::filesystem::path path, std::uint64_t *file_count,
                 std::atomic_uint64_t *total_line_count,
                 std::atomic_uint64_t *total_word_count,
                 std::atomic_uint64_t *total_char_count) {
    dirstat::Pool pool;
    for (auto const &dir_entry :
         std::filesystem::recursive_directory_iterator{path}) {
      if (!dir_entry.is_regular_file())
        continue;

      pool.push_job(std::bind(&dirstat::process_file, dir_entry.path(),
                              total_line_count, total_word_count,
                              total_char_count));
      ++*file_count;
    }
}
} // namespace dirstat
