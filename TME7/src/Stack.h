#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	sem_t mutex;
	sem_t stabpop;
	sem_t stabpush;
	T tab [STACKSIZE];
	size_t sz;
public :
	Stack () : sz(0) {
		memset(tab,0,sizeof tab) ;
		sem_init(&mutex, 1, 1);
		sem_init(&stabpop, 1, 0);
		sem_init(&stabpush, 1, STACKSIZE);
	}

	T pop () {
		// bloquer si vide
		sem_wait(&stabpop);
		sem_wait(&mutex);
		T toret = tab[--sz];
		sem_post(&mutex);
		sem_post(&stabpush);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&stabpush);
		sem_wait(&mutex);
		tab[sz++] = elt;
		sem_post(&mutex);
		sem_post(&stabpop);
	}

	~Stack() {
	    sem_destroy(&mutex);
	    sem_destroy(&stabpop);
	    sem_destroy(&stabpush);
	}
};

}
