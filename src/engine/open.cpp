#include "open.hpp"

namespace engine {
	void config::load(std::string config) {
		std::map<std::string, std::string> values;

		read(values, config);
		read(values, values["configFile"]);

		configFile = values["configFIle"];
		saveDIr = values["saveDIr"];
		wx0 = values["wx0"];
		wy0 = values["wy0"];
		wx1 = values["wx1"];
		wy1 = values["wy1"];
		mx0 = values["mx0"];
		my0 = values["my0"];
		mx1 = values["mx1"];
		my1 = values["my1"];
		title = values["title"];
	}

	menu::menu() {
		conf.load(configFile);
	}

	menu::~menu() {
		delete configFile;
		delete conf;
		delete manager;
	}

	menu::general() {
		return;
	}

	menu::window() {
		manager.display();
	}

	menu::display() {
		general();
		window();

		glFlush();
	}

	menu::control(unsigned char key, int x, int y) {
		return;
	}

	menu::run(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

		glutInitWindowPosition(x0, y0);
		glutInitWindowSize(x1 - x0, y1 - y0);
		glutCreateWindow(title);

		glutDisplayFunc(display);
		glutKeynoardFunc(control);

		std::vector<type::u16> size = {8};
		mod::openWorldConfig setup(size);
		mod::mod game(setup);

		manager = new e1d(game);

		glutMainLoop();
	}
}
