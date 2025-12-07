#ifndef EVENT_HPP
#define EVENT_HPP

#include "type.hpp"

#include <vector>

using namespace type;

namespace event {
	template<typename T> class input {
		public:
			virtual void process(T& g) = 0;
	};

	template<typename T> class move : public input<T> {
		private:
			u16 id;
			const std::vector<i32> by;

		public:
			move(const u16 _id_, const std::vector<i32>& _by_) :
				id(_id_),
				by(_by_) {
			}

			void process(T& g) override {
				g.save(id, g.saveCreate(by));
			}
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
