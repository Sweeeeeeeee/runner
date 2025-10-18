#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <vector>
#include <queue>

#include "data.hpp"
#include "type.hpp"
#include "vector.hpp"

using namespace type;

namespace game {
	// cyclic class defenition	
	class nothing;
	class wall;
	class hell;
	class heaven;
	class zone;
	class player;

	class field;
	
	class moveAction {
		private:
			u8 dimension;
			i32 to;
	
		public:
			moveAction(u8 _dimension_, i32 _to_);
	
			u8 dimensionGet() const;
			i32 toGet() const;
	};	

	// entities on the map
	class object {
		protected:
			std::vector<u16> koordinates;
	
			bool destroyObject;

			data::objectData information;
	
		public:
			object(const std::vector<u16>& _koordinates_, u8 _type_, u16 _groupId_);
		
			const std::vector<u16>& where() const;

			// should be an interface if cpp was any of a language, fuck u idiot who made this bullshit language
			bool interact(object& other);

			bool perform(field& map);
	
			void destroy();
	
			const data::objectData& informationGet() const;
	};
	
	// empty sapce
	class nothing : public object {
		public:
			nothing(const std::vector<u16>& _koordinates_);
	
			bool interact(object& other);
	
			bool perform(field& map);
	};
	
	// non breachable wall
	class wall : public object {
		public:
			wall(const std::vector<u16>& _koordinates_);
	
			bool interact(object& other);
			bool interact(zone& other);

			bool perform(field& map);
	};
	
	// kills evrything
	class hell : public object {
		public:
			hell(const std::vector<u16>& _koordinates_);
	
			bool interact(object& other);
			bool interact(zone& other);
			bool interact(player& other);
	
			bool perform(field& map);
	};
	
	// proclaims one a victor
	class heaven : public object {
		public:
			heaven(const std::vector<u16>& _koordinates_);
	
			bool interact(object& other);
			bool interact(zone& other);
			bool interact(player& other);
	
			bool perform(field& map);
	};

	// moving death zone
	class zone : public object {
		private:
			moveAction action;
	
		public:
			zone(const std::vector<u16>& koordinates, u8 _moveDimension_, i32 _to_);
	
			bool interact(object& other);
			bool interact(player& other);
	
			bool perform(field& map);
	};
	
	// player
	class player : public object {
		private:
			bool dead;
			bool won;
	
			u16 team;

			moveAction action;
	
		public:
			player(const std::vector<u16>& _koordinates_, u16 _team_);

			const std::vector<u16>& where() const;

			bool interact(object& other);
			bool interact(player& other);
			
			void save(const moveAction& _action_);
	
			bool perform(field& map);

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
	
			std::vector<object*> map;

			std::queue<object*> toProcess;

			u64 access(const std::vector<u16>& at) const;
	
		public:
			field(const std::vector<u16>& _size_);

			object* process();

			void change(const std::vector<u16>& at, object& assign);
			void empty(const std::vector<u16>& at);
	
			u8 dimensionsGet() const;
			u16 dimensionSizeGet(u8 id) const;
			object& operator [](const std::vector<u16>& at);
	};
		
	// game manager
	class game {
		private:
			u64 moveNumber;
			bool gameEnded;
	
			std::vector<player> players;
			std::vector<player*> activePlayers;
	
			std::vector<object> objects;
			std::vector<object*> activeObjects;
	
			field map;
	
		public:
			game(const std::vector<u16>& size, const std::vector<player>& _players_, const std::vector<object>& _objects_);
			void step();
	
			void save(u16 id, const moveAction& action);
	
			bool gameEndedGet() const;
	
			bool playerDeadGet(u16 id) const;
			bool playerWonGet(u16 id) const;
	
			const data::objectData& render(const std::vector<u16>& at);
	};
}

#endif // RUNNER_HPP
