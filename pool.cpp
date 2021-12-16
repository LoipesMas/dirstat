#include "pool.hpp"
#include <iostream>
#include <vector>

namespace dirstat {
Pool::Pool() : m_done(false) {
  int const thread_count = std::thread::hardware_concurrency();
  try {
    for (int i = 0; i < thread_count; ++i) {
      this->workers.push_back(std::thread(&Pool::worker_loop, this));
    }
  } catch (...) {
    this->m_done = true;
    throw;
  }
}

Pool::~Pool() {
  this->m_done = true;
  for (auto &t : this->workers) {
    if (t.joinable())
      t.join();
  }
}

void Pool::worker_loop() {
  while (true) {
    std::function<void()> task;
    {
      std::unique_lock<std::mutex> lock(this->m_queue_mutex);
      if (this->m_job_queue.empty()) {
        if (this->m_done) {
          break;
        }
        std::this_thread::yield();
        continue;
      }
      task = this->m_job_queue.front();
      this->m_job_queue.pop();
    }
    task();
  }
}

void Pool::push_job(std::function<void()> f) {
  std::unique_lock<std::mutex> lock(this->m_queue_mutex);
  this->m_job_queue.push(std::function<void()>(f));
}
} // namespace dirstat
