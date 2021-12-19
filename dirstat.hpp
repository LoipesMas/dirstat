#include <filesystem>
#include <atomic>
#include <fstream>
#include <mutex>

namespace dirstat {
// Holds all counts
struct Counts {
    std::mutex mutex;
    std::uint64_t file_count;
    std::uint64_t line_count;
    std::uint64_t word_count;
    std::uint64_t char_count;
};

// Processes file from given path.  
//  Counts lines, words, characters and adds them to given atomics.
void process_file(std::filesystem::path file_path,
                  Counts *counts);

// Runs `process_file` on all files in given directory (recursively).
void run_in_path(std::filesystem::path path,
                  Counts *counts);
} // namespace dirstat
