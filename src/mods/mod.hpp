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

			io::chan<data::objectData> updates;

			io::chan<event::input<game::game>> eventInChan;
			io::chan<event::output> eventOutChan;

		public:
			~mod();

			io::writer<event::input<game::game>>& eventWriterGet();
			io::reader<event::output>& eventReaderGet();
			io::reader<data::objectData>& loaderGet();

			virtual void run() = 0;
	};

	struct openWorldConfig {
		const std::vector<u16> size;

		openWorldConfig(const std::vector<u16>& _size_) :
			size(_size_) {
		}
	};

	class openWorld : public mod {
		private:
			const openWorldConfig setup;

		public:
			openWorld(const openWorldConfig& setup);

			const std::vector<u16>& sizeGet() const;
			
			void run();
	};
}

#endif // MOD_HPP
