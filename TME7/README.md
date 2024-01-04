
**TME7 Report**

---

#### Question 1

fichier pipe.cpp

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main (int argc, char **argv) {

	const char **argv1;
	const char **argv2;

	int Tube[2];

	pipe(Tube);

	int pipe_index;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "|") == 0) {
	        pipe_index = i;
            break;
        }
	}

	argv1 = (const char**)malloc(sizeof(const char*)*(pipe_index-1));
	argv2 = (const char**)malloc(sizeof(const char*)*(argc - pipe_index - 1));

	for (int i = 1; i < pipe_index; i++) {
	    argv1[i - 1] = argv[i];
	}
	argv1[pipe_index - 1] = nullptr;

	for (int i = pipe_index + 1, j = 0; i < argc; i++, j++) {
	    argv2[j] = argv[i];
	}
	argv2[argc - pipe_index - 1] = nullptr;

	//ajouter les arguments à argv2 + nullptr

	if (fork() == 0) {
		dup2(Tube[1], STDOUT_FILENO);
		close(Tube[1]);
		close(Tube[0]);
		execv(argv1[0], (char **)argv1);
		exit(1);
	} else {
		dup2(Tube[0], STDIN_FILENO);
		close(Tube[0]);
		close(Tube[1]);
		execv(argv2[0], (char **)argv2);
		exit(1);
	}

	return 0;
}

```

