#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "mod.hpp"
#include "io.hpp"
#include "game.hpp"
#include "eConfig.hpp"

namespace engine {
	class engineBase {
		protected:
			const config& conf;

			std::unique_ptr<mod::mod> game;
			
			io::reader<event::output>* reader;
			io::writer<event::input<game::game>>* writer;
			io::reader<data::objectData>* loader;

		public:
			engineBase(const config& _cconf_, std::unique_ptr<mod::mod> _game_);
			~engineBase();

			virtual void run() = 0;

			virtual void display() = 0;
	};
}

#endif // ENGINE_HPP
