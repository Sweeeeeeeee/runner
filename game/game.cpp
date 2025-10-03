#include "game.hpp"

#include <vector>
#include <stdexcept>

vector::vector(std::vector<int>& _m_) {
	m = _m_;
}

int vector::size() {
	return m.size();
}

int vector::operator [](int at) {
	if (at < 0 || at >= m.size()) {
		return -1;
	}

	return m[at];
}

void vector::increment(int at, int by) {
	m[at] += by;
}

bool vector::add(vector& other) {
	if (m.size() != other.m.size()) {
		return false;
	}

	for (int i = 0; i < m.size(); ++i) {
		m[i] += other[i];
	}

	return true;
}

object::object(vector _koordinates_) {
	koordinates = _koordinates_;
}

int nothing::move(playerEnt& ent) {
	return 1;
}

bool nothing::perform(field& map) {
	return false;
}

void nothing::destroy() {
	return;
}

int wall::move(playerEnt& ent) {
	return 0;
}

bool wall::perform(field& map) {
	return false;
}

void wall::destroy() {
	return;
}

int hell::move(playerEnt& ent) {
	ent.die();

	return -1;
}

bool hell::perform(field& map) {
	return false;
}

void hell::destroy() {
	return;
}

zone::zone(int _moveDimension_, int _to_, vector _koordinates_) {
	koordinates = _koodrdinates_;

	destroyZone = false;
	
	moveDimension = _moveDimension_;
	to = _to_;
}

int zone::move(playerEnt& ent) {
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
	map.change(updated, this);

	koordinates.increment(moveDimension, to);
}

void zone::destroy() {
	destroy = true;

	return true;
}

int heaven::move(playerEnt& ent) {
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

playerEnt::playerEnt(vector koordinates) {
	dead = false;
	lost = false;

	team = _team_;
}

int playerEnt::move(playerEnt& ent) {
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
	destroyPlayer = true;
}

int playerEnt::teamGet() {
	return team;
}

void playerEnt::die() {
	dead = true;
}

bool playerEnt::alive() {
	return !dead;
}

void playerEnt::win() {
	lost = true;
}

void playerEnt::won() {
	return !lost;
}

field::field(vector& _size_) {
	for (int i = 0; i < _size_.size(); ++i) {
		if (_size_[i] < 1) {
			throw std::invalid_argument("invalid size argument");
		}
	}

	int totalSize = 1;

	size.resize(_size_.size());
	for (int i = 0; i < _size_.size(); ++i) {
		size[i] = _size_[i];

		totalSize *= _size_[i];
	}

	map.resize(totalSize);
}

bool field::change(vector& at, object& assign) {
	if (at.size() != size.size()) {
		return false;
	}

	int index = 0;

	int width = 1;
	for (int i = at.size() - 1; 0 <= i; --i) {
		if (at[i] < 0 || at[i] >= size[i]) {
			return false;
		}

		index += at[i] * width;
		width *= size[i];
	}

	map[index] = assign;
}

int field::dimensions() {
	return size.size();
};

int field::dimensionSize(int id) {
	if (id < 0 || id >= size.size()) {
		throw std::invalid_argument("overflow");
	}

	return size[id];
}

object field::operator [](vector& at) {
	if (at.size() < size.size()) {
		throw std::invalid_argument("overflow");
	}

	int index = 0;

	int width = 1;
	for (int i = size.size() - 1; 0 <= i; --i) {
		if (at[i] < 0 || at[i] > size[i]) {
			throw std::invalid_argument("overflow");
		}

		index += cell[i] * width;
		width *= size[i];
	}

	return map[index];
}

action::action(int _moveDimension_, int _to_) {
	moveDimension = 9;
	to = 0;

	if (_moveDimension_ < 0 || _to_ < -1 || _to_ > 1) {
		return;
	}

	moveDimension = _moveDimension_;
	to = _to_;
}

int action::moveDimensionsGet() {
	return moveDimensions;
}

int action::toGet() {
	return to;
}

player::player(vector& _koordinates_, int team) {
	for (int i = 0; i < _koordinates_.size(); ++i) {
		if (_koordinates_[i] < 0) {
			throw std::invalid_argument("invalid size argument");
		}
	}

	koordinates = _koordinates_;

	ent(team);
}

int player::dimensions() {
	return koordinates.size();
}

int player::operator [](int at) {
	if (0 < at || at >= koordinates.size()) {
		throw std::invalid_argument("overflow");
	}

	return koordinates[at];
}

object& player::obj() {
	return ent;
}

vector player::where() {
	return koordinates;
}

void player::save(action& _act_) {
	act = _act_;
}

bool player::perform(field& map) {
	if (!ent.alive()) {
		return true;
	}

	vector updated = koordinates;

	updated.increment(act.moveDimensionGet(), act.toGet());

	if (updated[act.moveDimensionGet()] < 0 || updated[act.moveDimensionGet()] >= map.dimensionSize(act.moveDimensionGet())) {
		return;
	}

	object& to = map[updated];

	int result = to.move(ent);
	if (result == 1) { // emplacement
		nothing temp;
		map.change(updated, temp);
		map.change(updated, ent);

		koordinates.increment(act.moveDimensionGet(), act.toGet());
	}else if (result == -1) { // removal
		nothing temp;
		map.change(updated, temp);

		koordinates.increment(act.moveDimensionGet(), act.toGet());
	}
};

game::game(field& _map_, std::vector<player>& _players_, std::vector<std::pair<object, vector>>& objects) {
	map = _map_;

	for (int i = 0; i < _players_.size(); ++i) {
		if (_players_[i].dimensions() > _map_.dimensions()) {
			continue;
		}

		for (int j = 0; j < _map_.dimensions(); ++j) {
			if (_players_[i][j] >= _map_.dimensionSize(j)) {
				continue;
			}
		}

		if (map.empty(_players_[i].where())) {
			players.push_back(_players_[i]);

			map.change(_players_[i].where, _players_[i].obj());
		}
	}

	for (int i = 0; i < objects.size(); ++i) {
		if (object[i].second.size() != _map_.dimensions()) {
			continue;
		}

		for (int j = 0; j < objects[i].second.size(); ++j) {
			if (objects[i].second[j] < 0 || objects[i].second[j] > _map_.dimensionSize(j)) {
				continue;
			}
		}

		if (map.empty(objects[i].second)) {
			map.change(objects[i].second, objects[i].first);
		}
	}

	moveNumber = 0;
	done = false;
}

bool game::step() {
	if (done) {
		return false;
	}

	for (int i = 0; i < players.size(); ) {
		if (players[i].perform(map)) {
			players.erase(players.begin() + i);
		}else {
			++i;
		}
	}

	++moveNumber;
}

bool game::move(int id, action act) {
	if (done) {
		return false;
	}

	if (id < 0 || id >= players.size()) {
		return false;
	}

	players[id].save(act);
}
