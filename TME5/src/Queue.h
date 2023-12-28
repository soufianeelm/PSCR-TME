#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <cstdlib>
#include <mutex>
#include <condition_variable>

namespace pr {

// MT safe version of the Queue, non blocking.
template <typename T>
class Queue {
	T ** tab;
	const size_t allocsize;
	size_t begin;
	size_t sz;
	mutable std::mutex m;
	std::condition_variable cd;
	bool setup;

	// fonctions private, sans protection mutex
	bool empty() const {
		return sz == 0;
	}
	bool full() const {
		return sz == allocsize;
	}
public:
	Queue(size_t size) :allocsize(size), begin(0), sz(0), setup(true) {
		tab = new T*[size];
		memset(tab, 0, size * sizeof(T*));
	}
	size_t size() const {
		std::unique_lock<std::mutex> lg(m);
		return sz;
	}
	T* pop() {
		std::unique_lock<std::mutex> lg(m);
		if (setup) {
			while (this->empty())
				cd.wait(lg);
			if (this->full())
				cd.notify_all();
		}
		if (empty()) {
			return nullptr;
		}
		auto ret = tab[begin];
		tab[begin] = nullptr;
		sz--;
		begin = (begin + 1) % allocsize;

		return ret;
	}
	bool push(T* elt) {
		std::unique_lock<std::mutex> lg(m);
		if (setup) {
			while (this->full())
				cd.wait(lg);
			if (this->empty())
				cd.notify_all();
		}
		if (full()) {
			return false;
		}
		tab[(begin + sz) % allocsize] = elt;
		sz++;

		return true;
	}
	void bloquant(bool set) {
		std::unique_lock<std::mutex> lg(m);
		setup = set;
		cd.notify_all();
	}
	~Queue() {
		// ?? lock a priori inutile, ne pas detruire si on travaille encore avec
		for (size_t i = 0; i < sz; i++) {
			auto ind = (begin + i) % allocsize;
			delete tab[ind];
		}
		delete[] tab;
	}
};

}

#endif /* SRC_QUEUE_H_ */
