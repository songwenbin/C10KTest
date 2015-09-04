#include "server.h"
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>

/*  
void createPidFile(void)
{
	FILE *fp = fopen(pidfile, "w");
	if (fp) {
		fprintf(fp, "%d", (int)getpid());
		fclose(fp);
	}
}
*/

void daemonize(void)
{
	int fd;
	if (fork() != 0) exit(0);
	setsid();

	if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if (fd > STDERR_FILENO) {
			close(fd);
		}
	}
}

void sigtermHandler(int sig)
{
	int shutdown = 1;
}

void setupSingalHandler(void)
{
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sigtermHandler;
	sigaction(SIGTERM, &act, NULL);
}

int main(int argc, char *argv[])
{
	setupSingalHandler();
	initServer();
	startServer();
        return 0;
}
