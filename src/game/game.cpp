#include "game.hpp"

namespace game {
	information::information(u8 _type_, u16 _groupId_) :
		type(_type_),
		groupId(_groupId_) {
	}

	data::metaData information::parse() const {
		return data::metaData(type, groupId);
	}

	object::object(std::vector<u16> _koordinates_, u8 type, u16 groupId) : 
		koordinates(_koordinates_),
		info(type, groupId) {
	}

	data::metaData object::infoGet() const {
		return info.parse();
	}

	nothing::nothing(std::vector<u16>& _koordinates_) :
		object(_koordinates_, 0, -1) {
	}
	
	u8 nothing::move(playerEnt& ent) {
		return 1;
	}
	
	bool nothing::perform(field& map) {
		return false;
	}
	
	void nothing::destroy() {
		return;
	}
	
	wall::wall(std::vector<u16>& _koordinates_) :
		object(_koordinates_, 1, -2) {
	}
	
	u8 wall::move(playerEnt& ent) {
		return 0;
	}
	
	bool wall::perform(field& map) {
		return false;
	}
	
	void wall::destroy() {
		return;
	}
	
	hell::hell(std::vector<u16>& _koordinates_) :
		object(_koordinates_, 2, -3) {
	}
	
	u8 hell::move(playerEnt& ent) {
		ent.die();
	
		return -1;
	}
	
	bool hell::perform(field& map) {
		return false;
	}
	
	void hell::destroy() {
		return;
	}
	
	zone::zone(std::vector<u16>& _koordinates_, u8 _moveDimension_, i16 _to_) : 
		destroyZone(false), 
		object(_koordinates_, 3, -4),
		moveDimension(_moveDimension_),
		to(_to_) {
	}
	
	u8 zone::move(playerEnt& ent) {
		ent.die();
	
		return -1;
	}
	
	bool zone::perform(field& map) {
		if (destroyZone) {
			return false;
		}
	
		std::vector<u16> updated = koordinates;
		vector::increment(updated, moveDimension, to, map.dimensionSizeGet(moveDimension));
	
		map[updated].destroy();
	
		map.empty(koordinates);
		map.change(updated, *this);
	
		vector::increment(koordinates, moveDimension, to, map.dimensionSizeGet(moveDimension));
	
		return false;
	}
	
	void zone::destroy() {
		destroyZone = true;
	}
	
	heaven::heaven(std::vector<u16>& _koordinates_) :
		object(_koordinates_, 4, -5) {
	}
	
	u8 heaven::move(playerEnt& ent) {
		ent.die();
		ent.win();
	
		return -1;
	}
	
	bool heaven::perform(field& map) {
		return false;
	}
	
	void heaven::destroy() {
		return;
	}
	
	playerEnt::playerEnt(std::vector<u16>& _koordinates_, u16 _team_) : 
		dead(false), 
		won(false), 
		object(_koordinates_, 5, _team_),
		team(_team_) {
	}
	
	u8 playerEnt::move(playerEnt& ent) {
		if (team == ent.teamGet()) {
			return 0;
		}
	
		die();
		
		return 1;
	}
	
	bool playerEnt::perform(field& map) {
		return false;
	}
	
	void playerEnt::destroy() {
		die();
	}
	
	u16 playerEnt::teamGet() const {
		return team;
	}
	
	void playerEnt::die() {
		dead = true;
	}
	
	bool playerEnt::deadGet() const {
		return dead;
	}
	
	void playerEnt::win() {
		won = true;
	}
	
	bool playerEnt::wonGet() const {
		return won;
	}
	
	field::field(std::vector<u16>& _size_) : 
		size(_size_) {
		u64 totalSize = 1;
	
		size.resize(_size_.size());
		for (u8 i = 0; i < _size_.size(); ++i) {
			totalSize *= _size_[i];
		}
	
		std::vector<u16> temp(_size_.size(), 0);
		map.resize(totalSize, nothing(temp));
	}
	
	void field::change(std::vector<u16>& at, object& assign) {
		u8 index = 0;
	
		u64 width = 1;
		for (u8 i = at.size() - 1; 0 <= i; --i) {
			index += at[i] * width;
			width *= size[i];
		}
	
		map[index] = assign;
	}
	
	u8 field::dimensionsGet() const {
		return size.size();
	};
	
	u16 field::dimensionSizeGet(u8 id) const {
		return size[id];
	}
	
	object& field::operator [](std::vector<u16>& at) {
		u8 index = 0;
	
		u64 width = 1;
		for (u8 i = size.size() - 1; 0 <= i; --i) {
			index += at[i] * width;
			width *= size[i];
		}
	
		return map[index];
	}
	
	action::action(u8 _moveDimension_, i16 _to_) : 
		moveDimension(_moveDimension_), 
		to(_to_) {
	}
	
	u8 action::moveDimensionGet() const {
		return moveDimension;
	}
	
	u16 action::toGet() const {
		return to;
	}
	
	player::player(std::vector<u16>& _koordinates_, u16 team) : 
		won(false), 
		koordinates(_koordinates_),
		ent(_koordinates_, team),
		act(0, 0) {
	}
	
	u8 player::dimensionsGet() const {
		return koordinates.size();
	}
	
	u16 player::operator [](u8 at) const {
		return koordinates[at];
	}
	
	object& player::obj() {
		return ent;
	}
	
	std::vector<u16>& player::where() {
		return koordinates;
	}
	
	void player::save(action& _act_) {
		act = _act_;
	}
	
	bool player::perform(field& map) {
		if (ent.deadGet() || ent.wonGet()) {
			return true;
		}
	
		std::vector<u16> updated = koordinates;
	
		vector::increment(updated, act.moveDimensionGet(), act.toGet(), map.dimensionSizeGet(act.moveDimensionGet()));
	
		object& to = map[updated];
	
		u8 result = to.move(ent);
		if (result == 1) { // emplacement
			nothing temp(updated);
			map.change(updated, temp);
			map.change(updated, ent);
	
			vector::increment(koordinates, act.moveDimensionGet(), act.toGet(), map.dimensionSizeGet(act.moveDimensionGet()));
		}else if (result == -1) { // removal
			nothing temp(updated);
			map.change(updated, temp);
	
			vector::increment(koordinates, act.moveDimensionGet(), act.toGet(), map.dimensionSizeGet(act.moveDimensionGet()));
	
			return true;
		}
	
		return false;
	};
	
	bool player::wonGet() const {
		return won;
	}

	game::game(field& _map_, std::vector<player>& _players_, std::vector<std::pair<object, std::vector<u16>>>& objects) :
		moveNumber(0),
		gameEnded(false),
		map(_map_),
		playerLog(_players_) {
	
		for (u8 i = 0; i < _players_.size(); ++i) {
			players.push_back(&_players_[i]);
	
			map.change(_players_[i].where(), _players_[i].obj());
		}
	
		for (u8 i = 0; i < objects.size(); ++i) {	
			map.change(objects[i].second, objects[i].first);
		}
	}
	
	void game::step() {
		if (gameEnded) {
			return;
		}
	
		for (u8 i = 0; i < players.size(); ) {
			if ((*players[i]).perform(map)) {
				players.erase(players.begin() + i);
			}else {
				++i;
			}
		}
	
		if (players.empty()) {
			gameEnded = true;
		}
	
		++moveNumber;
	}
	
	void game::move(u16 id, action act) {
		if (gameEnded) {
			return;
		}
	
		(*players[id]).save(act);
	}
	
	bool game::gameEndedGet() const {
		return gameEnded;
	}
	
	bool game::playerDeadGet(u16 id) const {
		return playerLog[id].deadGet();
	}
	
	bool game::playerWonGet(u16 id) const {
		return playerLog[id].wonGet();
	}
	
	const object& game::render(std::vector<u16>& at) {
		return map[at];
	}
}
