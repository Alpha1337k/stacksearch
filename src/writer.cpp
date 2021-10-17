#include <stacksearch.hpp>

int	run_groff(std::string &towrite, int *fdin, int *fdout)
{
	char *args[4] = {(char *)"groff", (char *)"-man", (char *)"-Tutf8", 0};
	pid_t id;

	id = fork();
	if (id == 0)
	{
		if (dup2(fdin[PIPE_RD], STDIN_FILENO) == -1)
		{
			std::cerr << "syscalls forks failed!" << std::endl;
			exit(-1);
		}
		if (dup2(fdout[PIPE_WR], STDOUT_FILENO) == -1)
		{
			std::cerr << "syscalls forks failed!" << std::endl;
			exit(-1);
		}
		close(fdin[PIPE_RD]);
		close(fdin[PIPE_WR]);
		execvp(args[0], args);
		std::cerr << "error exec" << std::endl;
		exit (-1);
	}
	else
	{
		size_t i = 0;
		int ret = 0;
		do
		{
			ret = write(fdin[PIPE_WR], &towrite[i], towrite.length() - i);
			i += ret;
		} while (ret > 0 && i != towrite.length());
		close(fdin[PIPE_RD]);
		close(fdin[PIPE_WR]);
		int status = 0;
		waitpid(id, &status, 0);
		close(fdout[PIPE_WR]);
	}
	return (0);
}

int	run_less(int *fd)
{
	char *args[3] = {(char *)"less", (char *)"-R", 0};
	pid_t id = fork();
	if (id == 0)
	{
		if (dup2(fd[PIPE_RD], STDIN_FILENO) == -1)
		{
			std::cerr << "syscalls forks failed!" << std::endl;
			exit(-1);
		}
		execvp(args[0], args);
		exit(-1);
	}
	else
	{
		int status = 0;
		waitpid(id, &status, 0);
		close(fd[PIPE_RD]);
	}
	return (0);
}


int	display_page(std::string &towrite)
{
	int fd_groff[2];
	int fd_less[2];

	if (pipe(fd_groff) != 0 || pipe(fd_less) != 0)
	{
		std::cerr << "syscalls pipe failed!" << std::endl;
		exit(-1);		
	}
	run_groff(towrite, fd_groff, fd_less);
	run_less(fd_less);

	return (0);
}