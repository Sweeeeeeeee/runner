#include "vector.hpp"

namespace vector {
	void increment(std::vector<u16>& a, const std::vector<i32>& by, const std::vector<u16>& max) {
		for (int i = 0; i < a.size(); ++i) {
			if (i32(a[i]) + by[i] < 0 || i32(a[i]) + by[i] >= i32(max[i])) {
				return;
			}
		}

		for (int i = 0; i < a.size(); ++i) {
			a[i] = i32(a[i]) + by[i];
		}
	}

	bool equal(const std::vector<u16>& a, const std::vector<u16>& b) {
		for (int i = 0; i < a.size(); ++i) {
			if (a[i] != b[i]) {
				return false;
			}
		}

		return true;
	}
}
