#include "vector.hpp"

namespace vector {
	void increment(std::vector<u16>& vec, u8 dimension, i16 by, u16 topBorder) {
		if (vec[dimension] + by < 0) {
			vec[dimension] = 0;
		}else if (vec[dimension] + by > topBorder) {
			vec[dimension] = topBorder - 1;
		}else {
			vec[dimension] += by;
		}
	}
}
