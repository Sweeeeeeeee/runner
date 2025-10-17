#ifndef DATA_HPP
#define DATA_HPP

#include "type.hpp"

using namespace type;

namespace data {
	struct objectData {
		u8 type;
		u16 color;

		objectData(u8 _type_, u16 _color_);
	};
}

#endif // DATA_HPP
