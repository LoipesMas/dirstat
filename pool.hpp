#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>

namespace dirstat {
    class Pool {

        std::atomic_bool m_done;
        std::queue<std::function<void()>> m_queue;
        std::mutex m_queue_mutex;
        std::vector<std::thread> workers;

        public:
            Pool();
            ~Pool();
            void worker_loop();
            void push_job(std::function<void()> f);

    };

}
