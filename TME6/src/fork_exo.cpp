#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "rsleep.h"

unsigned int pv;
pid_t child;

void handler (int SIG) {
	if (SIG & SIGINT) {
		pv--;
		std::cout << "points de vie restant pour " << getpid() << " : " << pv << std::endl;
		if (pv == 0) {
			std::cout << "le processus "<< getpid() <<" se termine" << std::endl;
			exit(1);
		}
	}
}

void handler_luke (int SIG) {
	if (SIG & SIGINT) {
		std::cout << "coup paré" << std::endl;
	}
}

void handler_child (int SIG) {
	if (SIG & SIGCHLD) {
		child = wait(nullptr);
	}
}

void handler_alarm (int SIG) {
	if (SIG & SIGALRM) {
		child = -1;
	}
}

void attaque (pid_t adversaire) {
	struct sigaction sa;
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, nullptr);
	int result = kill(adversaire, SIGINT);
	if (result != 0) {
		exit(0);
	}
	randsleep();
}

void defense () {
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, nullptr);
	randsleep();
}

void defense_luke () {
	struct sigaction sa;
	sigset_t nmask, omask;
	sigfillset(&nmask);
	sa.sa_handler = handler_luke;
	sigaction(SIGINT, &sa, nullptr);
	sigprocmask(SIG_BLOCK, &nmask, &omask);
	randsleep();
	sigdelset(&nmask, SIGINT);
	sigsuspend(&nmask);
	sigprocmask(SIG_SETMASK, &omask, nullptr);
}

void combat_vador (pid_t adversaire) {
	pv = 10;
	while (1) {
		defense();
		attaque(adversaire);
	}
}

void combat_luke (pid_t adversaire) {
	pv = 10;
	while (1) {
		defense_luke();
		attaque(adversaire);
	}
}

int wait_till_pid_v1(pid_t pid) {
	pid_t child;

	while (child != pid) {
		child = wait(nullptr);
		if (child == -1) {
			return -1;
		}
	}

	return child;
}

int wait_till_pid_v2(pid_t pid, int sec) {
	child = 0;
	struct sigaction sa;
	sa.sa_handler = handler_child;
	sigaction(SIGCHLD, &sa, nullptr);
	sa.sa_handler = handler_alarm;
	sigaction(SIGALRM, &sa, nullptr);
	sigset_t mask;
	sigfillset(&mask);
	sigdelset(&mask, SIGCHLD);
	sigdelset(&mask, SIGALRM);
	alarm(sec);
	while (child != pid) {
		sigsuspend(&mask);
		if (child == pid) {
			alarm(0);
			break;
		} else if (child == -1) {
			return 0;
		}
	}
	return child;
}

int main () {
/*
	const int N = 3;
	int tot = 1;
	std::cout << "main pid=" << getpid() << std::endl;

	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		(i<N)? tot=1 : tot=0;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			tot++;
			if ( fork() == 0) {
				tot = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
		}
	}

	for (int i=1; i<=tot; i++) {
		wait(NULL);
	}*/

	if (fork() == 0) {
		pid_t p = getpid();
		if (int q = fork() == 0) {
			std::cout << "combat entre Vador : " << p << " et Luke : " << getpid() << std::endl;
			combat_luke(p);
		} else {
			combat_vador(q);
		}
	}

	return 0;
}
