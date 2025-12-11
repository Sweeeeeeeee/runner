#ifndef E2D_HPP
#define E2D_HPP

#include "mod.hpp"
#include "type.hpp"
#include "event.hpp"

#include <stdexcept>

class move {
	int lastX = -1;
};

namespace engine {
	class e1d : public engine {
		private:
			move data;

		public:
			e1d(const config::config& _conf_, mod::mod&& _game_);

			void run();

			void display();
	};
}

#endif // E2D_HPP
