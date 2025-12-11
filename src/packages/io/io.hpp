#ifndef IO_HPP
#define IO_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <any>

namespace io {
	template<typename T> class writer {
		private:
			std::queue<std::unique_ptr<T>>& queue;

			std::mutex& mutex;
			std::condition_variable& condition;

		public:
			writer(std::queue<std::unique_ptr<T>>& _queue_, std::mutex& _mutex_, std::condition_variable& _condition_) :
				queue(_queue_),
				mutex(_mutex_),
				condition(_condition_) {
			}

			void push(std::unique_ptr<T> value) {
				std::unique_lock<std::mutex> lock(mutex);
				queue.push(std::move(value));
				condition.notify_one();
			}
	};

	template<typename T> class reader {
		private:
			std::queue<std::unique_ptr<T>>& queue;

			std::mutex& mutex;
			std::condition_variable& condition;

		public:
			reader(std::queue<std::unique_ptr<T>>& _queue_, std::mutex& _mutex_, std::condition_variable& _condition_) :
				queue(_queue_),
				mutex(_mutex_),
				condition(_condition_) {
			}

			bool empty() {
				std::unique_lock<std::mutex> lock(mutex);
				
				return queue.empty();
			}

			std::unique_ptr<T> pop() {
				std::unique_lock<std::mutex> lock(mutex);
				condition.wait(lock, [this] {
						return !queue.empty();
					}
				);

				std::unique_ptr<T> value = std::move(queue.front());
				queue.pop();

				return value;
			}
	};

	template<typename T> class chan {
		private:
			std::queue<std::unique_ptr<T>> queue;

			std::mutex mutex;
			std::condition_variable condition;

			reader<T>* readerChan;
			writer<T>* writerChan;

		public:
			chan() :
				queue(), mutex(), condition() {
					
				readerChan = new reader<T>(queue, mutex, condition);
				writerChan = new writer<T>(queue, mutex, condition);
			};

			~chan() {
				delete readerChan;
				delete writerChan;
			}

			reader<T>& readerGet() {
				return *readerChan;
			}

			writer<T>& writerGet() {
				return *writerChan;
			}
	};
}

#endif // IO_HPP
