#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "eConfig.hpp"
#include "mod.hpp"
#include "type.hpp"
#include "e2d.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <string>

namespace engine {	
	class menu {
		private:
			std::string configFile = "config\\config.ec";
			config conf;

			e1d* manager;

		public:
			menu();
			~menu();

			void general();
			void window();
			void display();

			void control(unsigned char key, int x, int y);

			void run(int argc, char** argv);
	};
}

#endif // ENGINE_HPP
