#include <filesystem>
#include <atomic>
#include <fstream>

namespace dirstat {
void process_file(std::filesystem::path file_path,
                  std::atomic_uint64_t *total_line_count,
                  std::atomic_uint64_t *total_word_count,
                  std::atomic_uint64_t *total_char_count);
void run_in_cur_path(
                  std::uint64_t *file_count,
                  std::atomic_uint64_t *total_line_count,
                  std::atomic_uint64_t *total_word_count,
                  std::atomic_uint64_t *total_char_count);
} // namespace dirstat
