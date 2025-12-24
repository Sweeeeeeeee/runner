#ifndef ECONFIG_HPP
#define ECONFIG_HPP

#include "config.hpp"

#include <map>
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
}

#endif // ECONFIG_HPP
