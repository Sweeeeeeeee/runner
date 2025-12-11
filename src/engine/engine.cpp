#include "engine.hpp"

namespace engine {
	engine::engine(const config::config& _conf_, mod::mod&& _game_) :
		conf(_conf_),
		game(std::move(_game_)) {

		io::reader<event::output>* reader;
		io::writer<event::input<game::game>>* writer;
		io::reader<data::objectData>* loader;
	}

	engine::~engine() {
		delete conf;
		delete game;
		delete reader;
		delete writer;
		delete loader;
	}
}
