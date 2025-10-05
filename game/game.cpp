#include "game.hpp"

vector::vector() {
	return;
}

vector::vector(std::vector<u16>& _m_) : 
	m(_m_) {
}

u8 vector::size() {
	return m.size();
}

void vector::resize(u8 size) {
	m.resize(size);
}

u16 vector::operator [](u8 at) {
	return m[at];
}

void vector::increment(u8 at, u16 by) {
	m[at] += by;
}

bool vector::add(vector& other) {
	for (u8 i = 0; i < m.size(); ++i) {
		m[i] += other[i];
	}

	return true;
}

object::object(vector& _koordinates_) : 
	koordinates(_koordinates_) { 
}

nothing::nothing(vector& _koordinates_) : 
	object(_koordinates_) {
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

wall::wall(vector& _koordinates_) :
	object(_koordinates_) {
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

hell::hell(vector& _koordinates_) :
	object(_koordinates_) {
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

zone::zone(vector& _koordinates_, u8 _moveDimension_, u16 _to_) : 
	destroyZone(false), 
	object(_koordinates_), 
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

	vector updated = koordinates;
	updated.increment(moveDimension, to);

	map[updated].destroy();

	map.empty(koordinates);
	map.change(updated, *this);

	koordinates.increment(moveDimension, to);

	return false;
}

void zone::destroy() {
	destroyZone = true;
}

heaven::heaven(vector& _koordinates_) :
	object(_koordinates_) {
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

playerEnt::playerEnt(vector& _koordinates_, u16 team) : 
	dead(false), 
	won(false), 
	object(_koordinates_), 
	team(team) {
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

u16 playerEnt::teamGet() {
	return team;
}

void playerEnt::die() {
	dead = true;
}

bool playerEnt::deadGet() {
	return dead;
}

void playerEnt::win() {
	won = true;
}

bool playerEnt::wonGet() {
	return won;
}

field::field(vector& _size_) : 
	size(_size_) {
	u64 totalSize = 1;

	size.resize(_size_.size());
	for (u8 i = 0; i < _size_.size(); ++i) {
		totalSize *= _size_[i];
	}

	std::vector<u16> temp1(_size_.size(), 0);
	vector temp2(temp1);
	map.resize(totalSize, nothing(temp2));
}

void field::change(vector& at, object& assign) {
	u8 index = 0;

	u64 width = 1;
	for (u8 i = at.size() - 1; 0 <= i; --i) {
		index += at[i] * width;
		width *= size[i];
	}

	map[index] = assign;
}

u8 field::dimensionsGet() {
	return size.size();
};

u16 field::dimensionSizeGet(u8 id) {
	return size[id];
}

object& field::operator [](vector& at) {
	u8 index = 0;

	u64 width = 1;
	for (u8 i = size.size() - 1; 0 <= i; --i) {
		index += at[i] * width;
		width *= size[i];
	}

	return map[index];
}

action::action(u8 _moveDimension_, u16 _to_) : 
	moveDimension(_moveDimension_), 
	to(_to_) {
}

u8 action::moveDimensionGet() {
	return moveDimension;
}

u16 action::toGet() {
	return to;
}

player::player(vector& _koordinates_, u16 team) : 
	won(false), 
	koordinates(_koordinates_),
	ent(_koordinates_, team),
	act(0, 0) {
}

u8 player::dimensionsGet() {
	return koordinates.size();
}

u16 player::operator [](u8 at) {
	return koordinates[at];
}

object& player::obj() {
	return ent;
}

vector& player::where() {
	return koordinates;
}

void player::save(action& _act_) {
	act = _act_;
}

bool player::perform(field& map) {
	if (ent.deadGet() || ent.wonGet()) {
		return true;
	}

	vector updated = koordinates;

	updated.increment(act.moveDimensionGet(), act.toGet());

	object& to = map[updated];

	u8 result = to.move(ent);
	if (result == 1) { // emplacement
		nothing temp(updated);
		map.change(updated, temp);
		map.change(updated, ent);

		koordinates.increment(act.moveDimensionGet(), act.toGet());
	}else if (result == -1) { // removal
		nothing temp(updated);
		map.change(updated, temp);

		koordinates.increment(act.moveDimensionGet(), act.toGet());

		return true;
	}

	return false;
};

bool player::wonGet() {
	return won;
}

game::game(field& _map_, std::vector<player>& _players_, std::vector<std::pair<object, vector>>& objects) :
	moveNumber(0),
	done(false),
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
	if (done) {
		return;
	}

	for (u8 i = 0; i < players.size(); ) {
		if ((*players[i]).perform(map)) {
			players.erase(players.begin() + i);
		}else {
			++i;
		}
	}

	++moveNumber;
}

void game::move(u16 id, action act) {
	if (done) {
		return;
	}

	(*players[id]).save(act);
}

bool game::gameEnded() {
	return done;
}

bool game::playerDeadGet(u16 id) {
	return playerLog[id].deadGet();
}

bool game::playerWonGet(u16 id) {
	return playerLog[id].wonGet();
}
