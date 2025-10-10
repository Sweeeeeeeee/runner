#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <vector>

#include "data.hpp"
#include "type.hpp"
#include "vector.hpp"

using namespace type;

namespace game {
	// cyclic class defenition
	class playerEnt;
	
	class field;
	
	struct information {
		u8 type;
		u16 groupId;
	
		data::metaData parse() const;
		information(u8 _type_, u16 _team_);
	};
	
	// entities on the map
	class object {
		protected:
			std::vector<u16> koordinates;
	
			information info;
	
		public:
			object(std::vector<u16> _koordinates_, u8 _type_, u16 _groupId_);
			
			// manages non map entities move
			u8 move(playerEnt& ent); // should be an interface if cpp was any of a language, fuck u idiot who made this bullshit language
	
			// moves itself
			//
			// return value, true - destroy the object, false - keep the object
			bool perform(field& map); // same as move
	
			// call of element to destroy itself
			void destroy(); // same as move
	
			data::metaData infoGet() const;
	};
	
	// empty sapce
	class nothing : public object {
		public:
			nothing(std::vector<u16>& _koordinates_);
	
			u8 move(playerEnt& ent);
	
			bool perform(field& map);
	
			void destroy();
	};
	
	// non breachable wall
	class wall : public object {
		public:
			wall(std::vector<u16>& _koordinates_);
	
			u8 move(playerEnt& ent);
	
			bool perform(field& map);
	
			void destroy();
	
	};
	
	// kills evrything
	class hell : public object {
		public:
			hell(std::vector<u16>& _koordinates_);
	
			u8 move(playerEnt& ent);
	
			bool perform(field& map);
	
			void destroy();
	};
	
	// proclaims one a victor
	class heaven : public object {
		public:
			heaven(std::vector<u16>& _koordinates_);
	
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
			zone(std::vector<u16>& koordinates, u8 _moveDimension_, i16 _to_);
	
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
			playerEnt(std::vector<u16>& _koordinates_, u16 _team_);
	
			u8 move(playerEnt& ent);
	
			bool perform(field& map);
	
			void destroy();
	
			u16 teamGet() const;
	
			void die();
			bool deadGet() const;
			void win();
			bool wonGet() const;
	};
	
	// map
	class field {
		private:
			std::vector<u16> size;
	
			std::vector<object> map;
	
		public:
			field(std::vector<u16>& _size_);
			void change(std::vector<u16>& at, object& assign);
	
			u8 dimensionsGet() const;
			u16 dimensionSizeGet(u8 id) const;
			object& operator [](std::vector<u16>& at);
	};
	
	// instructions for player to move
	class action {
		private:
			u8 moveDimension;
			u16 to;
	
		public:
			action();
			action(u8 _moveDimension_, i16 _to_);
	
			u8 moveDimensionGet() const;
			u16 toGet() const;
	};
	
	// player
	class player {
		private:
			std::vector<u16> koordinates;
	
			action act;
	
			bool won;
	
			playerEnt ent;
	
		public:
			player(std::vector<u16>& _koordinates_, u16 team);
	
			u8 dimensionsGet() const;
			u16 operator [](u8 at) const;
	
			object& obj();
	
			std::vector<u16>& where();
	
			void save(action& act);
			bool perform(field& map);
	
			bool deadGet() const;
			bool wonGet() const;
	};
	
	// game manager
	class game {
		private:
			u64 moveNumber;
			bool gameEnded;
	
			std::vector<player> playerLog;
			std::vector<player*> players;
	
			std::vector<object> objects;
	
			field map;
	
		public:
			game(field& _map_, std::vector<player>& _players_, std::vector<std::pair<object, std::vector<u16>>>& objects);
			void step();
	
			void move(u16 id, action act);
	
			bool gameEndedGet() const;
	
			bool playerDeadGet(u16 id) const;
			bool playerWonGet(u16 id) const;
	
			const object& render(std::vector<u16>& at);
	};
}

#endif // RUNNER_HPP
