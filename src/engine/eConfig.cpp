#include "eConfig.hpp"

using namespace config;

namespace engine {
	void config::load(std::string config) {
		std::map<std::string, std::string> values;

		read(values, config);
		read(values, values["configFile"]);

		configFile = values["configFIle"];
		saveDir = values["saveDIr"];
		wx0 = std::stoi(values["wx0"]);
		wy0 = std::stoi(values["wy0"]);
		wx1 = std::stoi(values["wx1"]);
		wy1 = std::stoi(values["wy1"]);
		mx0 = std::stoi(values["mx0"]);
		my0 = std::stoi(values["my0"]);
		mx1 = std::stoi(values["mx1"]);
		my1 = std::stoi(values["my1"]);
		title = values["title"];
	}
}
