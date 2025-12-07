#include "game.hpp"
#include "mod.hpp"
#include "event.hpp"
#include "type.hpp"

int main() {
	mod::openWorldConfig config(std::vector<type::u16>({8, 8}));
	mod::openWorld game(config);

	io::reader<event::output>& reader = game.eventReaderGet();
	io::writer<event::input<game::game>>& writer = game.eventWriterGet();
	io::reader<data::objectData>& loader = game.loaderGet();

	for (game.run(); ; ) {
		writer.push(std::make_unique<event::move<game::game>>(std::move(event::move<game::game>(type::u16(0), std::vector<type::i32>({0, 0})))));
	}
}
