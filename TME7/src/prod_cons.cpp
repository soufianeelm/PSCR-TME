#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstdlib>
#include <csignal>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define CONS 10
#define PROD 10

using namespace std;
using namespace pr;

int *n;
vector<pid_t> proc;

void handler (int sig) {
	if (sig & SIGINT) {
		for (auto & pid : proc) {
			kill(pid, SIGTERM);
		}
		proc.clear();
	}
}

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {
	struct sigaction sa;
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, nullptr);

	//void* ptr = mmap(0, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

	int p = shm_open("/monshm", O_RDWR | O_EXCL | O_CREAT, 0666);
	n = (int*)mmap(NULL, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, p, 0);

	Stack<char> * s = new (n) Stack<char>();

	for (int i=0; i<PROD; i++) {
		pid_t pp = fork();
		if (pp==0) {
			producteur(s);
			return 0;
		}
	}

	for (int i=0; i<CONS; i++) {
		pid_t pc = fork();
		if (pc==0) {
			consomateur(s);
			return 0;
		} else {
			proc.push_back(pc);
		}
	}

	wait(0);
	wait(0);

	s->~Stack();
	//munmap(ptr, sizeof(Stack<char>));
	munmap(n, sizeof(Stack<char>));
	shm_unlink("/monshm");
	return 0;
}

