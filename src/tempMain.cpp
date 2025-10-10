#include <iostream>

#include "game.hpp"
#include "type.hpp"

using namespace type;

void output(game::game& g, std::vector<u16>& size) {
	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			std::vector<u16> cell = {i, j};
			data::metaData displayInfo = g.render(cell).infoGet();

			if (displayInfo.type == 0) {
				std::cout << "w";
			}else {
				std::cout << "p";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	std::vector<u16> size = {2, 3};

	game::field map(size);

	std::vector<u16> koordinates1 = {0, 0};
	std::vector<u16> koordinates2 = {0, 1};
	std::vector<game::player> players = {game::player(koordinates1, 0), game::player(koordinates2, 1)};

	std::vector<std::pair<game::object, std::vector<u16>>> objectList;

	game::game g(map, players, objectList);

	for (; !g.gameEndedGet(); ) {
		u8 D1, D2;
		i16 To1, To2;

		std::cin >> D1 >> To1;
		std::cin >> D2 >> To2;

		g.move(0, game::action(D1, To1));
		g.move(1, game::action(D2, To2));

		g.step();

		output(g, size);
	}
}
