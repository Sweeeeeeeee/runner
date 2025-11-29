#include "event.hpp"

namespace event {
	template<typename T> void input<T>::process(T& g) {
		return;
	}

	template<typename T> move<T>::move(const u16 _id_, const std::vector<u16>& _by_) :
		id(_id_),
		by(_by_) {
	}

	template<typename T> void move<T>::process(T& g) {
		g.save(id, by);
	}

	output::output(const outputEvent _type_) :
		type(_type_) {
	}
}
