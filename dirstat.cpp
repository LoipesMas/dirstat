#include "dirstat.hpp"

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
  while (std::getline(file, line)) {
    if (!line.empty())
      ++word_count;
    for (auto c : line) {
      ++char_count;
      if (c == ' ')
        ++word_count;
    }
    ++line_count;
  }

  file.close();
  *total_line_count += line_count;
  *total_word_count += word_count;
  *total_char_count += char_count;
}
} // namespace dirstat
