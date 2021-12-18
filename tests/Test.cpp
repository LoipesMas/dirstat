#include "../dirstat.hpp"
#include <atomic>
#include <gtest/gtest.h>

struct Test : public ::testing::Test {
  dirstat::Counts counts;
  std::filesystem::path cur_path = std::filesystem::current_path();

  virtual void SetUp() override {
    std::cout << std::filesystem::current_path() << std::endl;
    cur_path = std::filesystem::current_path().concat("/test_files/");
    counts.file_count = 0;
    counts.line_count = 0;
    counts.word_count = 0;
    counts.char_count = 0;
  }
};

TEST_F(Test, ProccessFile1) {
  dirstat::process_file(cur_path.concat("file1.txt"), &counts);
  EXPECT_EQ(0, counts.file_count);
  EXPECT_EQ(1, counts.line_count);
  EXPECT_EQ(4, counts.word_count);
  EXPECT_EQ(15, counts.char_count);
}
TEST_F(Test, ProccessFile2) {
  dirstat::process_file(cur_path.concat("file3.txt"), &counts);
  EXPECT_EQ(0, counts.file_count);
  EXPECT_EQ(16, counts.line_count);
  EXPECT_EQ(16, counts.word_count);
  EXPECT_EQ(65535, counts.char_count);
}
TEST_F(Test, ProcessDirectory) {
  dirstat::run_in_path(cur_path, &counts);
  EXPECT_EQ(3, counts.file_count);
  EXPECT_EQ(33, counts.line_count);
  EXPECT_EQ(36, counts.word_count);
  EXPECT_EQ(131085, counts.char_count);
}
