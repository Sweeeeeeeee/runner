#ifndef IO_HPP
#define IO_HPP

#include <queue>
#include <mutex>
#include <conditional_variable>

namespace io {
	template<typename T> class chan {
		private:
			std::queue<T> queue;

			std::mutex mutex;
			std::conditional_variable condition;

			reader<T>& readerChan;
			writer<T>& writerChan;

		public:
			chan();

			reader<T>& readerGet();
			writer<T>& writerGet();
	};

	template<typename T> class writer {
		private:
			std::queue<T>& queue;

			std::mutex& mutex;
			std::conditional_variable& condition;

		public:
			writer(std::queue<T>& _queue_, std::mutex& _mutex_, std::conditional_variable& _condition_);
			
			void push(T value);
	};

	template<typename T> class reader {
		private:
			std::queue<T>& queue;

			std::mutex& mutex;
			std::conditional_variable& condition;

		public:
			reader(std::queue<T>& _queue_, std::mutex& _mutex_, std::conditional_variable& _condition_);

			T& pop();
	};
}

#endif // IO_HPP
