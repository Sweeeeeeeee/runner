#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>
#include <fstream>

namespace config {
	void read(std::map<std::string, std::string>& values, std::string filename);
}

#endif // CONFIG_HPP
