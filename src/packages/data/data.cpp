#include "data.hpp"

namespace data {
	objectDataManager::objectDataManager(const std::vector<u16>& _koordinates_, const u8 _type1_, const u16 _type2_) :
		time(0),
		koordinates(1, {0, _koordinates_}),
		type1(1, {0, _type1_}),
		type2(1, {0, _type2_}) {
	}

	const std::vector<u16>& objectDataManager::koordinatesGet(const u64 time) const {
		return *koordinates[koordinates[time].first].second;
	}
	
	const std::vector<u16>& objectDataManager::koordinatesGetLatest() const {
		return *koordinates[koordinates.back().first].second;
	}

	u8 objectDataManager::type1Get(const u64 time) const {
		return *type1[type1[time].first].second;
	}

	u8 objectDataManager::type1GetLatest() const {
		return *type1[type1.back().first].second;
	}
	
	u16 objectDataManager::type2Get(const u64 time) const {
		return *type2[type2[time].first].second;
	}
	
	u16 objectDataManager::type2GetLatest() const {
		return *type2[type2.back().first].second;
	}

	void objectDataManager::koordinatesChange(const std::vector<u16>& to) {
		++time;

		koordinates.push_back({time, to});
		type1.push_back({lastType1, std::nullopt});
		type2.push_back({lastType2, std::nullopt});
	}

	void objectDataManager::type1Change(const u8 to) {
		++time;

		koordinates.push_back({time, std::nullopt});
		type1.push_back({lastType1, to});
		type2.push_back({lastType2, std::nullopt});
	}

	void objectDataManager::type2Change(const u16 to) {
		++time;

		koordinates.push_back({time, std::nullopt});
		type1.push_back({lastType1, std::nullopt});
		type2.push_back({lastType2, to});
	}

	u64 objectDataManager::timeGet() const {
		return time;
	}

	objectData objectDataManager::save() const {
		return objectData(*this);
	}

	objectData::objectData(const objectDataManager& _parent_) :
		parent(_parent_),
		time(parent.timeGet()) {
	}

	const std::vector<u16>& objectData::koordinatesGet() const {
		return parent.koordinatesGet(time);
	}

	u8 objectData::type1Get() const {
		return parent.type1Get(time);
	}

	u16 objectData::type2Get() const {
		return parent.type2Get(time);
	}
}
