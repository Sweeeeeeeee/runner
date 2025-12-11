#include "e2d.hpp"

namespace engine {
	e1d::e1d(const config::config& _conf_, mod::mod&& _game_) :
		engine(_conf_, _game_),
		data() {

		if (game.sizeGet().size() != 1) {
			throw std::invalid_argument("invalid size");
		}
	}

	void e1d::run() {
		game.run();
	}

	void e1d::display() {
		int size = game.sizeGet()[0];

		for (int i = 0; i < size; ++i) {
			GlBegin(GL_POLYGON);
			glVertex2i(
				config.wx1 + i * (config.wx2 - config.wx1) / (size + 1), 
				config.wy1 + (config.wy2 - config.wy1) / 2
			)
			glVertex2i(
				config.wx1 + (i + 1) * (config.wx2 - config.wx1) / (size + 1), 
				config.wy1 + (config.wy2 - config.wy1) / 2
			)
			glVertex2i(
				config.wx1 + (i + 1) * (config.wx2 - config.wx1) / (size + 1), 
				config.wy1 + (config.wy2 - config.wy1) / 2 + (config.wy2 - config.wy1)
			)
			glVertex2i(
				config.wx1 + i * (config.wx2 - config.wx1) / (size + 1), 
				config.wy1 + (config.wy2 - config.wy1) / 2 + (config.wy2 - config.wy1)
			)
			GlEnd();
		}

		for (; !reader.empty(); ) {
			std::unique_ptr<data::objectData> obj = reader.pop();
			int index = obj.koordinatesGet()[0];

			glBegin(GL_POLYGON);
			glVertex2i(
				config.wx1 + index * (config.wx2 - config.wx1) / (size + 1), 
				config.wy1 + (config.wy2 - config.wy1) / 2
			)
			glVertex2i(
				config.wx1 + (index + 1) * (config.wx2 - config.wx1) / (size + 1), 
				config.wy1 + (config.wy2 - config.wy1) / 2
			)
			glVertex2i(
				config.wx1 + (index + 1) * (config.wx2 - config.wx1) / (size + 1), 
				config.wy1 + (config.wy2 - config.wy1) / 2 + (config.wy2 - config.wy1)
			)
			glVertex2i(
				config.wx1 + index * (config.wx2 - config.wx1) / (size + 1), 
				config.wy1 + (config.wy2 - config.wy1) / 2 + (config.wy2 - config.wy1)
			)
		}

		glFlush();
	}
}
