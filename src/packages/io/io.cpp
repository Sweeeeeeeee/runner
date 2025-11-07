#include "io.hpp"

namespace io {
	writer(std::queue<T>& _queue_, std::mutex& _mutex_, std::condition_variable& _condition_) :
		queue(_queue_),
		mutex(_mutex_),
		condition(_condition_) {
	}

	void writer::push(T value) {
		std::unique_lock<std::mutex> lock(mutex);
		queue.push(std::move(value));
		condition.notify_one();
	}

	reader(std::queue<T>& _queue_, std::mutex& _mutex_, std::condition_variable& _condition_) :
		queue(_queue_),
		mutex(_mutex_),
		condition(_condition_) {
	}

	T& reader::pop() {
		std::unique_lock<std::mutex> lock(mutex);
		condition.wait(lock, [this] { return !queue.empty() });

		T value - std::move(queue.front());
		queue.pop();

		return value;
	}
}
