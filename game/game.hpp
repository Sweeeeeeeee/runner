#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <vector>

class vector {
	private:
		std::vector<int> m;

	public:
		vector(std::vector<int>& _m_);

		int size();
		int operator [](int at);

		void increment(int at, int by);
		bool add(vector& other);
};

class playerEnt;

class field;

class object {
	private:
		vector koordinates;

	public:
		virtual int move(playerEnt& ent);

		virtual bool perform(field& map);

		virtual void destroy();
};

class nothing : public object {
	public:
		int move(playerEnt& ent);

		bool perform(field& map);

		void destroy();
};

class wall : public object {
	public:
		int move(playerEnt& ent);

		bool perform(field& map);

		void destroy();

};

class hell : public object {
	public:
		int move(playerEnt& ent);

		bool perform(field& map);

		void destroy();
};

class heaven : public object {
	public:
		int move(playerEnt& ent);

		bool perform(field& map);

		void destroy();
};

class zone : public object {
	private:
		bool destroyZone;

		int moveDimension;
		int to;

	public:
		zone(int _moveDimension_, int _to_);

		int move(playerEnt& ent);

		bool perform(field& map);

		void destroy();
};

class playerEnt : public object {
	private:
		bool destroyPlayer;

		bool dead;
		bool lost;

		int team;

	public:
		playerEnt(int _team_);

		int teamGet();

		void die();
		bool alive();
		void win();
		bool won();
};

class field {
	private:
		vector size;

		std::vector<object> map;

	public:
		field(vector& _size_);
		bool empty(vector& at);
		bool change(vector& at, object& assign);

		int dimensions();
		int dimensionSize(int id);
		object operator [](vector& at);
};

class action {
	private:
		int moveDimension;
		int to;

	public:
		action(int _moveDimension_, int _to_);

		int moveDimensionGet();
		int toGet();
};

class player {
	private:
		vector koordinates;

		action act;

		bool won;

		object ent;

	public:
		player(vector& _koordinates_, int team);
		int dimensions();
		int operator [](int at);

		object& obj();

		vector where();

		void save(action& act);
		bool perform(field& map);
};

class game {
	private:
		int moveNumber;
		bool done;

		std::vector<player> players;
		std::vector<object> objects;

		field map;

	public:
		game(field& _map_, std::vector<player>& _players_, std::vector<object>& objects);
		bool step();

		bool move(int id, action act);
};

#endif // RUNNER_HPP
