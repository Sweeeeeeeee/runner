#include "io.hpp"

namespace io {
	template<typename T> writer(std::queue<T>& _queue_, std::mutex& _mutex_, std::condition_variable& _condition_) :
		queue(_queue_),
		mutex(_mutex_),
		condition(_condition_) {
	}

	template<typename T> void writer::push(T& value) {
		std::unique_lock<std::mutex> lock(mutex);
		queue.push(std::move(value));
		condition.notify_one();
	}

	template<typename T> reader(std::queue<T>& _queue_, std::mutex& _mutex_, std::condition_variable& _condition_) :
		queue(_queue_),
		mutex(_mutex_),
		condition(_condition_) {
	}

	template<typename T> T reader::pop() {
		std::unique_lock<std::mutex> lock(mutex);
		condition.wait(lock, [this] { return !queue.empty() });

		T value - std::move(queue.front());
		queue.pop();

		return std::move(value);
	}
}
