#include "game.hpp"

namespace game {
	moveAction::moveAction(u8 _dimension_, i32 _to_) : 
		dimension(_dimension_),
		to(_to_) {
	}
	
	u8 moveAction::dimensionGet() const {
		return dimension;
	}
	
	i32 moveAction::toGet() const {
		return to;
	}

	object::object(const std::vector<u16>& _koordinates_, u8 type, u16 groupId) : 
		destroyObject(false),
		koordinates(_koordinates_),
		information(type, groupId) {
	}

	const std::vector<u16>& object::where() const {
		return koordinates;
	}

	bool object::interact(object& other) {
		return false;
	}

	bool object::perform(field& map) {
		return false;
	}

	void object::destroy() {
		destroyObject = true;
	}

	const data::objectData& object::informationGet() const {
		return information;
	}

	nothing::nothing(const std::vector<u16>& _koordinates_) :
		object(_koordinates_, 0, 0) {
	}
	
	bool nothing::interact(object& other) {
		destroy();

		return true;
	}
	
	bool nothing::perform(field& map) {
		return false;
	}	
	
	wall::wall(const std::vector<u16>& _koordinates_) :
		object(_koordinates_, 1, 0) {
	}
	
	bool wall::interact(object& other) {
		return false;
	}

	bool wall::interact(zone& other) {
		destroy();

		return true;
	}
	
	bool wall::perform(field& map) {
		return false;
	}	
	
	hell::hell(const std::vector<u16>& _koordinates_) :
		object(_koordinates_, 1, 1) {
	}
	
	bool hell::interact(object& other) {
		return false;
	}

	bool hell::interact(zone& other) {
		destroy();

		return true;
	}

	bool hell::interact(player& other) {
		other.die();

		return false;
	}
	
	bool hell::perform(field& map) {
		return false;
	}	
	
	heaven::heaven(const std::vector<u16>& _koordinates_) :
		object(_koordinates_, 1, 3) {
	}
	
	bool heaven::interact(object& other) {
		return false;
	}

	bool heaven::interact(zone& other) {
		destroy();

		return true;
	}
	
	bool heaven::interact(player& other) {
		other.win();
		other.die();

		other.destroy();

		return false;
	}
	
	bool heaven::perform(field& map) {
		return false;
	}
		
	zone::zone(const std::vector<u16>& _koordinates_, u8 _moveDimension_, i32 _to_) : 
		object(_koordinates_, 1, 2),
		action(_moveDimension_, _to_) {
	}

	bool zone::interact(object& other) {
		return false;
	}

	bool zone::interact(player& other) {
		other.die();

		other.destroy();

		return false;
	}
	
	bool zone::perform(field& map) {
		if (destroyObject) {
			return false;
		}

		std::vector<u16> updated = koordinates;

		vector::increment(updated, action.dimensionGet(), action.toGet(), map.dimensionSizeGet(action.dimensionGet()));

		if (map[updated].interact(*this)) {
			vector::increment(koordinates, action.dimensionGet(), action.toGet(), map.dimensionSizeGet(action.dimensionGet()));
			map.change(koordinates, *this);
		}

		return !destroyObject;
	}
	
	player::player(const std::vector<u16>& _koordinates_, u16 _team_) : 
		dead(false), 
		won(false), 
		object(_koordinates_, 2, _team_),
		team(_team_),
		action(0, 0) {
	}

	const std::vector<u16>& player::where() const {
		return koordinates;
	}

	bool player::interact(object& other) {
		die();

		destroy();

		return true;
	}

	bool player::interact(player& other) {
		if (other.teamGet() == teamGet()) {
			return false;
		}

		die();

		destroy();

		return true;
	}

	void player::save(const moveAction& _action_) {
		action = _action_;
	}

	bool player::perform(field& map) {
		if (destroyObject) {
			return true;
		}

		std::vector<u16> updated = koordinates;

		vector::increment(updated, action.dimensionGet(), action.toGet(), map.dimensionSizeGet(action.dimensionGet()));

		if (map[updated].interact(*this)) {
			vector::increment(koordinates, action.dimensionGet(), action.toGet(), map.dimensionSizeGet(action.dimensionGet()));
			map.change(koordinates, *this);
		}

		return destroyObject;
	};	
	
	u16 player::teamGet() const {
		return team;
	}
	
	void player::die() {
		dead = true;
	}
	
	bool player::deadGet() const {
		return dead;
	}
	
	void player::win() {
		won = true;
	}
	
	bool player::wonGet() const {
		return won;
	}

	u64 field::access(const std::vector<u16>& at) const {
		u64 index = 0;
	
		u64 width = 1;
		for (i16 i = size.size() - 1; 0 <= i; --i) {
			index += at[i] * width;
			width *= size[i];
		}

		return index;
	}
	
	field::field(const std::vector<u16>& _size_) : 
		size(_size_) {
		u64 totalSize = 1;
	
		for (u8 i = 0; i < _size_.size(); ++i) {
			totalSize *= _size_[i];
		}
	
		std::vector<u16> tempKoordinates(_size_.size(), 0);
		nothing tempObject(tempKoordinates);
		map.resize(totalSize, &tempObject);
	}

	void field::change(const std::vector<u16>& at, object& assign) {
		map[access(at)] = &assign;
	}

	void field::empty(const std::vector<u16>& at) {
		nothing temp(at);
		map[access(at)] = &temp;
	}
	
	u8 field::dimensionsGet() const {
		return size.size();
	};
	
	u16 field::dimensionSizeGet(u8 id) const {
		return size[id];
	}
	
	object& field::operator [](const std::vector<u16>& at) {
		return *map[access(at)];
	}

	game::game(const std::vector<u16>& size, const std::vector<player>& _players_, const std::vector<object>& _objects_) :
		moveNumber(0),
		gameEnded(false),
		map(size),
		players(_players_),
		objects(_objects_) {
	
		for (u8 i = 0; i < _players_.size(); ++i) {
			activePlayers.push_back(&players[i]);
	
			map.change(players[i].where(), players[i]);
		}
	
		for (u8 i = 0; i < objects.size(); ++i) {
			activeObjects.push_back(&objects[i]);

			map.change(objects[i].where(), objects[i]);
		}
	}
	
	void game::step() {
		if (gameEnded) {
			return;
		}
	
		for (u8 i = 0; i < activePlayers.size(); ) {
			if ((*activePlayers[i]).perform(map)) {
				activePlayers.erase(activePlayers.begin() + i);
			}else {
				++i;
			}
		}
	
		if (activePlayers.empty()) {
			gameEnded = true;
		}
	
		++moveNumber;
	}
	
	void game::save(u16 id, const moveAction& action) {
		if (gameEnded) {
			return;
		}

		players[id].save(action);
	}
	
	bool game::gameEndedGet() const {
		return gameEnded;
	}
	
	bool game::playerDeadGet(u16 id) const {
		return players[id].deadGet();
	}
	
	bool game::playerWonGet(u16 id) const {
		return players[id].wonGet();
	}
	
	const data::objectData& game::render(const std::vector<u16>& at) {
		return map[at].informationGet();
	}
}
