#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

size_t strlen( char *s) {
	size_t len = 0;
	while (*s++) len++;
	return len;
}
int streq( char *s1,  char *s2) {
	if (!s1 || !s2) return 0;
	while (*s1 && *s2) {
		if (*s1 != *s2) return 0;
		s1++;
		s2++;
	}
	return *s1 == *s2;
}
int is_next_pipe( char **argv) {
	int i = 0;
	while (argv[i]) {
		if (streq(argv[i], "|")) return 1;
		if (streq(argv[i], ";")) return 0;
		i++;
	}
	return 0;
}

char **get_params(char **argv) {
	int i = 0;
	while (argv[i] && !streq(argv[i], "|") && !streq(argv[i], ";")) i++;
	char **params = (char **)malloc(sizeof(char *) * (i + 1));
	for (int j = 0; j < i; j++) {
		params[j] = argv[j];
	}
	params[i] = NULL;
	return params;
}

void exec_cmd(char **argv, char **envp, int infd, int outfd) {
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		if (infd != 0) {
			dup2(infd, 0);
			close(infd);
		}
		if (outfd != 1) {
			dup2(outfd, 1);
			close(outfd);
		}
		char **params = get_params(argv);
		execve(params[0], params, envp);
	} else {
		if (infd != 0) close(infd);
		if (outfd != 1) close(outfd);
		waitpid(pid, NULL, 0);
	}
}

void pipe_cmd(char **argv, char **envp, int infd, int outfd) {
	int pipefd[2];
	pipe(pipefd);
	int i = 0;
	while (argv[i] && !streq(argv[i], "|")) i++;
	pid_t pid = fork();
	if (pid == 0) {
		close(infd);
		close(pipefd[1]);
		argv += i + 1;
		if (is_next_pipe(argv)) {
			pipe_cmd(argv, envp, pipefd[0], outfd);
		} else {
			exec_cmd(argv, envp, pipefd[0], outfd);
		}
		exit(0);
	} else {
		close(pipefd[0]);
		if (outfd != 1) close(outfd);
		exec_cmd(argv, envp, infd, pipefd[1]);
	}
	waitpid(pid, NULL, 0);
}

int main(int c, char **v, char **envp) {
	int i = 1;
	while (v[i]) {
		if (streq(v[i], ";")) {
			i += 1;
		} else {
			if (is_next_pipe(v + i)) {
				pipe_cmd(v + i, envp, 0, 1);
			} else {
				exec_cmd(v + i, envp, 0, 1);
			}
			while (v[i] && !streq(v[i], ";")) i++;
		}
	}
}