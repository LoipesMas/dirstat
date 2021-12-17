#include <filesystem>
#include <atomic>
#include <fstream>

namespace dirstat {

// Processes file from given path.  
//  Counts lines, words, characters and adds them to given atomics.
void process_file(std::filesystem::path file_path,
                  std::atomic_uint64_t *total_line_count,
                  std::atomic_uint64_t *total_word_count,
                  std::atomic_uint64_t *total_char_count);

// Runs `process_file` on all files in given directory (recursively).
void run_in_path(std::filesystem::path path,
                  std::uint64_t &file_count,
                  std::atomic_uint64_t *total_line_count,
                  std::atomic_uint64_t *total_word_count,
                  std::atomic_uint64_t *total_char_count);
} // namespace dirstat
