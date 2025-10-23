#include <iostream>

#include "game.hpp"
#include "type.hpp"

using namespace type;

void output(game::game& g, std::vector<u16>& size) {
	for (int i = 0; i < size[0]; ++i) {
		for (int j = 0; j < size[1]; ++j) {
			std::vector<u16> cell = {i, j};
			const data::objectData& display = g.render(cell);

			if (display.type == 0) {
				std::cout << "n";
			}else if (display.type == 2) {
				std::cout << "p";
			}else {
				std::cout << "!";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	std::vector<u16> size = {2, 3};

	std::vector<u16> koordinates1 = {0, 0};
	std::vector<u16> koordinates2 = {0, 1};
	std::vector<game::player> players = {game::player(koordinates1, 0), game::player(koordinates2, 1)};

	std::vector<game::object> objects;

	game::game g(size, players, objects);

	for (; !g.gameEndedGet(); ) {
		int x1, y1, x2, y2;

		std::cin >> x1 >> y1;
		std::cin >> x2 >> y2;

		std::vector<i32> mp1 = {x1, y1};
		std::vector<i32> mp2 = {x2, y2};
		g.save(0, game::moveAction(mp1));
		g.save(1, game::moveAction(mp2));

		g.step();

		output(g, size);
	}
}
