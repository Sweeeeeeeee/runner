#include "engine.hpp"

namespace engine {
	engineBase::engineBase(const config& _conf_, std::unique_ptr<mod::mod> _game_) :
		conf(_conf_),
		game(std::move(_game_)) {

		io::reader<event::output>* reader;
		io::writer<event::input<game::game>>* writer;
		io::reader<data::objectData>* loader;
	}

	engineBase::~engineBase() {
		delete reader;
		delete writer;
		delete loader;
	}
}
