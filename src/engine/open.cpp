#include "open.hpp"

namespace engine {
	menu::menu() {
		conf.load(configFile);
	}

	menu::~menu() {
		delete manager;
	}

	void menu::general() {
		return;
	}

	void menu::window() {
		(*manager).display();
	}

	void menu::display() {
		general();
		window();

		glFlush();
	}

	void menu::control(unsigned char key, int x, int y) {
		return;
	}

	void menu::run(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

		glutInitWindowPosition(conf.mx0, conf.my0);
		glutInitWindowSize(conf.mx1 - conf.mx0, conf.my1 - conf.my0);
		glutCreateWindow(conf.title);

		glutDisplayFunc(display);
		glutKeyboardFunc(control);

		std::vector<type::u16> size = {8};
		mod::openWorldConfig setup(size);
		mod::openWorld game(setup);

		manager = new e1d(conf, std::move(std::make_unique<mod::mod>(game)));

		glutMainLoop();
	}
}
