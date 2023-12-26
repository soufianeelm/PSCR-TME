#pragma once
#include <cstddef>


namespace pr {

template<typename iterator, typename T>
iterator find(iterator begin, iterator end, const T& target) {
	iterator it;
	for (it = begin; it != end; it++){
		if (target==*it){
			break;
		}
	}
	return it;
}

template<typename iterator, typename Pred>
iterator find_if(iterator begin, iterator end, Pred pred) {
	iterator it;
	for (it = begin; it != end; it++){
		if (pred(*it)){
			break;
		}
	}
	return it;
}

template<typename iterator>
size_t count (iterator begin, iterator end) {
	iterator it;
	size_t cpt = 0;
	for (it = begin; it != end; it++) {
		cpt++;
	}
	return cpt;
}

template<typename iterator, typename T>
size_t count_if_equal (iterator begin, iterator end, const T& val) {
	iterator it;
	size_t cpt = 0;
	for (it = begin; it != end; it++) {
		if (*it==val)
			cpt++;
	}
	return cpt;
}

}
