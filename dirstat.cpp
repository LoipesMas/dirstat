#include "dirstat.hpp"
#include "pool.hpp"

namespace dirstat {
void process_file(std::filesystem::path file_path, dirstat::Counts *counts) {
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

  std::unique_lock<std::mutex> lock(counts->mutex);
  counts->line_count += line_count;
  counts->word_count += word_count;
  counts->char_count += char_count;
}

void run_in_path(std::filesystem::path path, dirstat::Counts *counts) {
  dirstat::Pool pool;
  for (auto const &dir_entry :
       std::filesystem::recursive_directory_iterator{path}) {
    if (!dir_entry.is_regular_file())
      continue;

    pool.push_job([=]() { dirstat::process_file(dir_entry.path(), counts); });
    counts->file_count++;
  }
}
} // namespace dirstat
