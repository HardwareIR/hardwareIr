#pragma once

#include <vector>
#include <set>

template<typename T>
class OrderedSet: public std::vector<T> {
	using vec_t = std::vector<T>;
	using value_type = typename vec_t::value_type;

	std::set<T> _set;

	void push_back(const value_type& __x) {
		if (_set.find(__x) == _set.end()) {
			vec_t::push_bak(__x);
			_set.insert(__x);
		}
	}

	void push_back_many(const vec_t & vec) {
		for (auto & i: vec)
			push_back(i);
	}
};
