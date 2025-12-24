#include "e2d.hpp"

namespace engine {
	e1d::e1d(const config& _conf_, std::unique_ptr<mod::mod> _game_) :
		engineBase(_conf_, std::move(_game_)),
		data() {

		if ((*game).sizeGet().size() != 1) {
			throw std::invalid_argument("invalid size");
		}
	}

	void e1d::run() {
		(*game).run();
	}

	void e1d::display() {
		int size = (*game).sizeGet()[0];

		for (int i = 0; i < size; ++i) {
			glBegin(GL_POLYGON);
			glVertex2i(
				conf.wx0 + i * (conf.wx1 - conf.wx0) / (size + 1), 
				conf.wy0 + (conf.wy1 - conf.wy0) / 2
			);
			glVertex2i(
				conf.wx0 + (i + 1) * (conf.wx1 - conf.wx0) / (size + 1), 
				conf.wy0 + (conf.wy1 - conf.wy0) / 2
			);
			glVertex2i(
				conf.wx0 + (i + 1) * (conf.wx1 - conf.wx0) / (size + 1), 
				conf.wy0 + (conf.wy1 - conf.wy0) / 2 + (conf.wy1 - conf.wy0)
			);
			glVertex2i(
				conf.wx0 + i * (conf.wx1 - conf.wx0) / (size + 1), 
				conf.wy0 + (conf.wy1 - conf.wy0) / 2 + (conf.wy1 - conf.wy0)
			);
			glEnd();
		}

		for (; !(*loader).empty(); ) {
			std::unique_ptr<data::objectData> obj = (*loader).pop();
			int index = (*obj).koordinatesGet()[0];

			glBegin(GL_POLYGON);
			glVertex2i(
				conf.wx0 + index * (conf.wx1 - conf.wx0) / (size + 1), 
				conf.wy0 + (conf.wy1 - conf.wy0) / 2
			);
			glVertex2i(
				conf.wx0 + (index + 1) * (conf.wx1 - conf.wx0) / (size + 1), 
				conf.wy0 + (conf.wy1 - conf.wy0) / 2
			);
			glVertex2i(
				conf.wx0 + (index + 1) * (conf.wx1 - conf.wx0) / (size + 1), 
				conf.wy0 + (conf.wy1 - conf.wy0) / 2 + (conf.wy1 - conf.wy0)
			);
			glVertex2i(
				conf.wx0 + index * (conf.wx1 - conf.wx0) / (size + 1), 
				conf.wy0 + (conf.wy1 - conf.wy0) / 2 + (conf.wy1 - conf.wy0)
			);
			glEnd();
		}

		glFlush();
	}
}
