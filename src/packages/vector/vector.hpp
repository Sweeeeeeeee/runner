#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>

#include "type.hpp"

using namespace type;

namespace vector {
	void increment(std::vector<u16>& vec, u8 dimension, i16 by, u16 topBorder);
}

#endif // VECTOR_HPP
