#include "mod.hpp"

namespace mod {
	io::writer<event::input>& eventWriterGet() {
		return eventInChan.writerGet();
	}

	io::reader<event::output>& eventReaderGet() {
		return eventOutChan.readerGet();
	}

	const std::vector<u16>& mod::sizeGet() const {
		return g.sizeGet();
	}

	const std::pair<data::objectData&, u64> mod::render() {
		return updates.pop();
	}	

	openWorld::openWorld(openWorldConfig& setup) {
		std::vector<u16> koordinates(setup.size.size());

		for (int i = 0; i < setup.size.size(); ++i) {
			koordinates[i] = setup.size[i] / 2;
		}

		std::vector<game::player> players = {game::player(koordinates, 0)};

		std::vector<game::object> objects; // to be added after debug
	
		g = new game::game(updates.writerGet(), setup.size, players, objects);
	}

	~openWorld::openWorld() {
		~(*g)();
	}

	void openWorld::run() {
		io::reader<event::input> reader = eventInChan.readerGet();
		io::writer<event::output> writer = eventOutChan.writerGet();


	}
}
