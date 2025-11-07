#include "game.hpp"

namespace game {
	moveAction::moveAction(const std::vector<i32>& _by_) : 
		by(_by_) {
	}

	moveAction::moveAction(int bySize) : 
		by(std::vector<i32>(bySize)) {
	}
	
	const std::vector<i32>& moveAction::byGet() const {
		return by;
	}

	object::object(const std::vector<u16>& koordinates, const u8 type, const u16 groupId) : 
		destroyObject(false),
		information(koordinates, type, groupId) {
	}

	const std::vector<u16>& object::where() const {
		return information.koordinatesGetLatest();
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

	const std::pair<const data::objectData&, u64> object::informationGet() const {
		return {std::ref(information), information.timeGet()};
	}

	nothing::nothing(const std::vector<u16>& koordinates) :
		object(koordinates, 0, 0) {
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
		
	zone::zone(const std::vector<u16>& _koordinates_, moveAction& _action_) : 
		object(_koordinates_, 1, 2),
		action(_action_) {
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
			return true;
		}

		std::vector<u16>& koordinates(information.koordinatesGetLatest());

		std::vector<u16> updated(koordinates);

		vector::increment(updated, action.byGet(), map.sizeGet());

		if (!vector::equal(koordinates, updated) && map[updated].interact(*this)) {
			information.koordinatesChange(updated);
			map.move(koordinates, updated);
		}

		return destroyObject;
	}

	player::player(const std::vector<u16>& _koordinates_, u16 _team_) : 
		dead(false),
		won(false),
		object(_koordinates_, 2, _team_),
		team(_team_),
		action(koordinates.size()) {
	}

	const std::vector<u16>& player::where() const {
		return information.koordinatesGetLatest();
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

		std::vector<u16>& koordinates(information.koordinatesGetLatest());

		std::vector<u16> updated = information.koordinatesGetLatest();

		vector::increment(updated, action.byGet(), map.sizeGet());

		if (!vector::equal(koordinates, updated) && map[updated].interact(*this)) {
			information.koordinatesChange(updated);	
			map.move(koordinates, updated);
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
	
	field::field(io::writer<const data::objectData> _writer_, const std::vector<u16>& _size_) : 
		time(0),
		writer(_writer_),
		size(_size_) {
		u64 totalSize = 1;
	
		for (u8 i = 0; i < _size_.size(); ++i) {
			totalSize *= _size_[i];
		}

		map.resize(totalSize);

		std::vector<u16> tempKoordinates(_size_.size(), 0);
		u8 step = 0;
		for (int i = 0; i < map.size(); ++i) {
			for (int index = i; (index % size.size[step]) == 0 && index != 0; index /= size.size[step]) {
				++tempKoordinates[step];

				++step;
			}

			nothing* obj = new nothing(tempKoordinates);
			
			map[i] = obj;
			toProcess.push(obj);

			writer.push(obj.informtaionGet());
		}
	}

	object* field::process() {
		if (toProcess.empty()) {
			return nullptr;
		}

		object* temp = toProcess.front();
		toProcess.pop();
		return temp;
	}

	void field::change(const std::vector<u16>& at, object& assign) {
		map[access(at)] = &assign;

		writer.push(asssign.informationGet());
	}

	void field::empty(const std::vector<u16>& at) {
		nothing temp(at);
		map[access(at)] = &temp;

		writer.push(temp.informationGet());
	}

	void field::move(const std::vector<u16>& from, std::vector<u16>& to) {
		u64 koordinatesFrom = access(from);
		u64 koordinatesTo = access(to);

		map[koordinatesFrom] = map[koordinatesTo];

		object* obj = new nothing(from);
		map[koordinatesFrom] = obj;
		toProcess.push(obj);

		writer.push(map[koordinatesFrom].informationGet());
		writer.push(map[koordinatesTo].informationGet());
	}
	
	const std::vector<u16>& field::sizeGet() const {
		return size;
	}

	object& field::operator [](const std::vector<u16>& at) {
		return *map[access(at)];
	}

	game::game(io::writer<const std::pair<data::objectData&, u64>>& _writer_, const std::vector<u16>& size, const std::vector<player>& _players_, const std::vector<object>& _objects_) :
		moveNumber(0),
		gameEnded(false),
		writer(_writer_),
		map(_writer_, size),
		players(_players_),
		objects(_objects_) {

		for (object* obj = map.process(); obj != nullptr; obj = map.process()) {
			objects.push_back(*obj);
			activeObjects.push_back(obj);
		}
	
		for (u8 i = 0; i < players.size(); ++i) {
			activePlayers.push_back(&players[i]);

			map.change(players[i].where(), players[i]);
		}
	
		for (u8 i = 0; i < _objects_.size(); ++i) {
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

			for (object* obj = map.process(); obj != nullptr; obj = map.process()) {
				objects.push_back(*obj);
				activeObjects.push_back(obj);
			}
		}

		for (u8 i = 0; i < activeObjects.size(); ) {
			if ((*activeObjects[i]).perform(map)) {
				activeObjects.erase(activeObjects.begin() + i);
			}else {
				++i;
			}

			for (object* obj = map.process(); obj != nullptr; obj = map.process()) {
				objects.push_back(*obj);
				activeObjects.push_back(obj);
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
}
