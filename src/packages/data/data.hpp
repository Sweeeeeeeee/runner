#ifndef DATA_HPP
#define DATA_HPP

#include "type.hpp"

#include <vector>
#include <optional>

using namespace type;

namespace data {
	class objectData;

	class objectDataManager {
		private:
			std::vector<std::pair<u64, const std::optional<std::vector<u16>>>> koordinates;

			std::vector<std::pair<const u64, const std::optional<u8>>> type1;
			std::vector<std::pair<const u64, const std::optional<u16>>> type2;

			u64 lastKoordinates;
			u64 lastType1;
			u64 lastType2;

			u64 time;

		public:
			objectDataManager(const std::vector<u16>& _koordinates_, const u8 _type1_, const u16 _type2_);

			const std::vector<u16>& koordinatesGet(const u64 time) const;
			const std::vector<u16>& koordinatesGetLatest() const;

			u8 type1Get(const u64 time) const;
			u8 type1GetLatest() const;
			u16 type2Get(const u64 time) const;
			u16 type2GetLatest() const;

			void koordinatesChange(const std::vector<u16>& to);

			void type1Change(const u8 to);
			void type2Change(const u16 to);

			u64 timeGet() const;

			objectData save() const;
	};

	class objectData {
		private:
			const objectDataManager& parent;

			const u64 time;

		public:
			objectData(const objectDataManager& _parent_);

			const std::vector<u16>& koordinatesGet() const;
			
			u8 type1Get() const;
			u16 type2Get() const;
	};
}

#endif // DATA_HPP
