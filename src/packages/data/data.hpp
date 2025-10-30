#ifndef DATA_HPP
#define DATA_HPP

#include "type.hpp"

using namespace type;

namespace data {
	class objectData {
		private:
			std::vector<std::vector<u16>> koordinates;

			std::vector<u8> type1;
			std::vector<u16> type2;

		public:
			objectData(std::vector<u16>& _koordinates_, u8 _type1_, u16 _type2_);

			const std::vector<u16>& koordinatesGet(u64 time);
			const std::vector<u16>& koordinatesGetLatest();

			u8 type1Get(u64 time);
			u8 type1GetLatest();
			u16 type2Get(u64 time);
			u16 type2GetLatest();

			void koordinatesChange(std::vector<u16>& to);

			void type1Change(u8 to);
			void type2Change(u16 to);
	};
}

#endif // DATA_HPP
