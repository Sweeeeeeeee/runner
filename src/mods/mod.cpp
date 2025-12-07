#include "mod.hpp"
#include "io.hpp"
#include "data.hpp"

namespace mod {
	mod::~mod() {
		delete g;
	}

	io::writer<event::input<game::game>>& mod::eventWriterGet() {
		return eventInChan.writerGet();
	}

	io::reader<event::output>& mod::eventReaderGet() {
		return eventOutChan.readerGet();
	}

	io::reader<data::objectData>& mod::loaderGet() {
		return updates.readerGet();
	}

	openWorld::openWorld(const openWorldConfig& _setup_) : 
		setup(_setup_) {
		std::vector<u16> koordinates(setup.size.size());

		for (int i = 0; i < setup.size.size(); ++i) {
			koordinates[i] = setup.size[i] / 2;
		}

		std::vector<game::player> players = {game::player(koordinates, 0)};

		std::vector<game::object> objects; // to be added after debug
	
		g = new game::game(updates.writerGet(), setup.size, players, objects);
	}

	const std::vector<u16>& openWorld::sizeGet() const {
		return setup.size;
	}

	void openWorld::run() {
		io::reader<event::input<game::game>>& reader = eventInChan.readerGet();
		io::writer<event::output>& writer = eventOutChan.writerGet();

		for (; !(*g).gameEndedGet(); ) {
			(*reader.pop()).process(*g);
		}

		writer.push(std::make_unique<event::output>(std::move(event::crash)));
	}
}
