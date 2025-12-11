#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "config.hpp"
#include "mod.hpp"
#include "type.hpp"

#include <string>

namespace engine {
	struct config {
		std::string configFile;
		std::string saveDir;

		int wx0, wy0, wx1, wy1;
		int mx0, my0, mx1, my1;

		std::string title;

		void load(std::string config);
	};

	class menu {
		private:
			std::string configFIle = "config\\config.ec";
			config conf;

			e1d* manager;

		public:

			menu();
			~menu();

			void general();
			void window();
			void display();

			void run();
	}
}

#endif // ENGINE_HPP
