#ifndef E2D_HPP
#define E2D_HPP

#include "mod.hpp"
#include "type.hpp"
#include "event.hpp"
#include "eConfig.hpp"
#include "engine.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdexcept>

class move {
	int lastX = -1;
};

namespace engine {
	class e1d : public engineBase {
		private:
			move data;

		public:
			e1d(const config& _conf_, std::unique_ptr<mod::mod> _game_);

			void run();

			void display();
	};
}

#endif // E2D_HPP
