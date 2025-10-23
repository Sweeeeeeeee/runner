#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>

#include "type.hpp"

using namespace type;

namespace vector {
	void increment(std::vector<u16>& a, const std::vector<i32>& by, const std::vector<u16>& max);

	bool equal(const std::vector<u16>& a, const std::vector<u16>& b);
}

#endif // VECTOR_HPP
