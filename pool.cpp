#include "pool.hpp"
#include <iostream>
#include <vector>

namespace dirstat {
Pool::Pool() : m_done(false) {
  // Creates one worker per available thread
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
  // Wait for all workers to finish
  for (auto &t : this->workers) {
    if (t.joinable())
      t.join();
  }
}

void Pool::worker_loop() {
  while (true) {
    std::function<void()> job;
    {
      // Lock job queue
      std::unique_lock<std::mutex> lock(this->m_queue_mutex);
      // Check if task is ready
      if (this->m_job_queue.empty()) {
        // If empty and done, quit
        if (this->m_done) {
          break;
        }
        // If not done, wait
        std::this_thread::yield();
        continue;
      }
      // Get new job
      job = this->m_job_queue.front();
      this->m_job_queue.pop();
    }
    // Do job
    job();
  }
}

void Pool::push_job(std::function<void()> f) {
  std::unique_lock<std::mutex> lock(this->m_queue_mutex);
  this->m_job_queue.push(std::function<void()>(f));
}
} // namespace dirstat
