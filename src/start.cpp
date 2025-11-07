#include "game.hpp"
#include "mod.hpp"
#include "type.hpp"

int main() {
	mod::openWorldConfig config(std::vector<type::u32>({8, 8}));
	mod::openWorld game(config);

	io::reader<event::output>& reader = game.eventReaderGet();
	io::writer<event::input>& writer = game.eventWriterGet();

	for (game.run(); ; ) {
		writer.push(std::vector<type::u16>({0, 0}));
	}
}
