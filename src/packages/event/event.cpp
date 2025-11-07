#include "event.hpp"

namespace event {
	void move::process(T& g) {
		g.save(id, by);
	}

	output::output(const outputEvent _type_) :
		type(_type_) {
	}
}
