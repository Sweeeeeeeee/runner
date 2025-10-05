#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <vector>
#include <unordered_map>
#include <cstdint>

// for safety
typedef std::uint8_t u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

// acsees managment adaptor
class vector {
	private:
		std::vector<u16> m;

	public:
		vector();
		vector(std::vector<u16>& _m_);

		u8 size();
		void resize(u8 size);
		u16 operator [](u8 at);

		void increment(u8 at, u16 by);
		bool add(vector& other);
};

// cyclic class defenition
class playerEnt;

class field;

// entities on the map
class object {
	protected:
		vector koordinates;

	public:
		object(vector& _koordinates_);

		// manages non map entities move
		virtual u8 move(playerEnt& ent);

		// moves itself
		//
		// return value, true - destroy the object, false - keep the object
		virtual bool perform(field& map);

		// call of element to destroy itself
		virtual void destroy();
};

// empty sapce
class nothing : public object {
	public:
		nothing(vector& _koordinates_);

		u8 move(playerEnt& ent);

		bool perform(field& map);

		void destroy();
};

// non breachable wall
class wall : public object {
	public:
		wall(vector& _koordinates_);

		u8 move(playerEnt& ent);

		bool perform(field& map);

		void destroy();

};

// kills evrything
class hell : public object {
	public:
		hell(vector& _koordinates_);

		u8 move(playerEnt& ent);

		bool perform(field& map);

		void destroy();
};

// proclaims one a victor
class heaven : public object {
	public:
		heaven(vector& _koordinates_);

		u8 move(playerEnt& ent);

		bool perform(field& map);

		void destroy();
};

// moving death zone
class zone : public object {
	private:
		bool destroyZone;

		// rules to move
		u8 moveDimension;
		u16 to;

	public:
		zone(vector& koordinates, u8 _moveDimension_, u16 _to_);

		u8 move(playerEnt& ent);

		bool perform(field& map);

		void destroy();
};

// object representing player on the map
class playerEnt : public object {
	private:
		// values to report to the player
		bool dead;
		bool won;

		u16 team;

	public:
		playerEnt(vector& _koordinates_, u16 _team_);

		u8 move(playerEnt& ent);

		bool perform(field& map);

		void destroy();

		u16 teamGet();

		void die();
		bool deadGet();
		void win();
		bool wonGet();
};

// map
class field {
	private:
		vector size;

		std::vector<object> map;

	public:
		field(vector& _size_);
		bool empty(vector& at);
		void change(vector& at, object& assign);

		u8 dimensionsGet();
		u16 dimensionSizeGet(u8 id);
		object& operator [](vector& at);
};

// instructions for player to move
class action {
	private:
		u8 moveDimension;
		u16 to;

	public:
		action();
		action(u8 _moveDimension_, u16 _to_);

		u8 moveDimensionGet();
		u16 toGet();
};

// player
class player {
	private:
		vector koordinates;

		action act;

		bool won;

		playerEnt ent;

	public:
		player(vector& _koordinates_, u16 team);

		u8 dimensionsGet();
		u16 operator [](u8 at);

		object& obj();

		vector& where();

		void save(action& act);
		bool perform(field& map);

		bool deadGet();
		bool wonGet();
};

// game manager
class game {
	private:
		u64 moveNumber;
		bool done;

		std::vector<player> playerLog;
		std::vector<player*> players;

		std::vector<object> objects;

		field map;

	public:
		game(field& _map_, std::vector<player>& _players_, std::vector<std::pair<object, vector>>& objects);
		void step();

		void move(u16 id, action act);

		bool gameEnded();

		bool playerDeadGet(u16 id);
		bool playerWonGet(u16 id);
};

#endif // RUNNER_HPP
