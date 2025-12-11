#include "config.hpp"

namespace config {
	void read(std::map<std::string, std::string>& values, std::string filename) {
		std::ifstream file(filename);

		std::string s;
		for (; std::getline(file, s); ) {
			int a = 0;
			int b = 1;
			int c = s.size();
			
			for (int i = 0; i < s.size(); ++i) {
				if (s[i] == ' ') {
					a = i;
				
					break;
				}
			}
	
			bool first = false;
			for (int i = a; i < s.size(); ++i) {
				if (s[i] != ' ') {
					if (s[i] == '=') {
						if (first) {
							b = i;

							break;
						}

						first = true;
					}else {
						b = i;

						break;
					}
				}
			}

			for (int i = b; i < s.size(); ++i) {
				if (s[i] == ' ') {
					c = i;

					break;
				}
			}

			values[s.substr(a)] = s.substr(b, c - b - 1);
		}
	}
}
