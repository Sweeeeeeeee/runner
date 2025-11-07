#ifndef EVENT_HPP
#define EVENT_HPP

#include "type.hpp"

#include <vector>

using namespace type;

namespace event {
	template <typename T>class input {
		public:
			virtual void process(T& g) = 0;
	};

	template <typename T>class move : public input<T> {
		private:
			u16 id;
			std::vector<u16> by;

		public:
			void process(T& g) override;
	};

	enum outputEvent {
		win,
		end,
		crash
	};

	class output {
		public:
			const outputEvent type;
			
			output(const outputEvent _type_);
	};
}

#endif // EVENT_HPP
