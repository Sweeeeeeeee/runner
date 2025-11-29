#ifndef EVENT_HPP
#define EVENT_HPP

#include "type.hpp"

#include <vector>

using namespace type;

namespace event {
	template<typename T> class input {
		public:
			void process(T& g);
	};

	template<typename T> class move : public input<T> {
		private:
			u16 id;
			const std::vector<u16> by;

		public:
			move(const u16 _id_, const std::vector<u16>& _by_);

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
