#ifndef MOD_HPP
#define MOD_HPP

#include "game.hpp"
#include "io.hpp"
#include "type.hpp"
#include "data.hpp"
#include "event.hpp"

namespace mod {
	class mod {
		protected:
			game::game* g;

			io::chan<const std::pair<data::objectData&, u64>> updates;

			io::chan<event::input>& eventInChan;
			io::chan<event::output>& eventOutChan;

		public:
			io::writer<event::input>& eventWriterGet();
			io::reader<event::output>& eventReaderGet();

			const std::vector<u16>& sizeGet() const;
			const data::objectData& render();

			virtual void run() = 0;
	};

	struct openWorldConfig {
		std::vector<u16> size;
	};

	class openWorld : public mod {
		public:
			openWorld(openWorldConfig& setup);
			~openWorld();

			void run();
	};
}

#endif // MOD_HPP
