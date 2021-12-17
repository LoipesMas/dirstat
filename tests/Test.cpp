#include "../dirstat.hpp"
#include <atomic>
#include <gtest/gtest.h>

struct Test : public ::testing::Test {
  std::uint64_t file_count = 0;
  std::atomic_uint64_t total_line_count = 0;
  std::atomic_uint64_t total_word_count = 0;
  std::atomic_uint64_t total_char_count = 0;
  std::filesystem::path cur_path = std::filesystem::current_path();

  virtual void SetUp() override {
    std::cout << std::filesystem::current_path() << std::endl;
    cur_path = std::filesystem::current_path().concat("/test_files/");
    total_line_count = 0;
    total_word_count = 0;
    total_char_count = 0;
  }
};

TEST_F(Test, ProccessFile1) {
  dirstat::process_file(cur_path.concat("file1.txt"), &total_line_count,
                        &total_word_count, &total_char_count);
  EXPECT_EQ(0, file_count);
  EXPECT_EQ(1, total_line_count.load());
  EXPECT_EQ(4, total_word_count.load());
  EXPECT_EQ(15, total_char_count.load());
}
TEST_F(Test, ProccessFile2) {
  dirstat::process_file(cur_path.concat("file3.txt"), &total_line_count,
                        &total_word_count, &total_char_count);
  EXPECT_EQ(0, file_count);
  EXPECT_EQ(16, total_line_count.load());
  EXPECT_EQ(16, total_word_count.load());
  EXPECT_EQ(65535, total_char_count.load());
}
TEST_F(Test, ProcessDirectory) {
  dirstat::run_in_path(cur_path, file_count, &total_line_count,
                       &total_word_count, &total_char_count);
  EXPECT_EQ(3, file_count);
  EXPECT_EQ(33, total_line_count.load());
  EXPECT_EQ(36, total_word_count.load());
  EXPECT_EQ(131085, total_char_count.load());
}
