#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "mod.hpp"
#include "io.hpp"
#include "game.hpp"

namespace engine {
	class engine {
		private:
			const config::config& conf;

			mod::mod game;
			
			io::reader<event::output>* reader;
			io::writer<event::input<game::game>>* writer;
			io::reader<data::objectData>* loader;

		public:
			engine(const config& _cconf_, mod::mod&& _game_);
			~engine();

			virtual void run() = 0;

			virtual void display() = 0;
	};
};

#endif // ENGINE_HPP
