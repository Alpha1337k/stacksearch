#include <stacksearch.hpp>

int	run_groff(std::string &towrite, char **env, int *fdin, int *fdout)
{
	char *args[4] = {(char *)"/bin/groff", (char *)"-man", (char *)"-Tascii", 0};
	pid_t id;

	if (dup2(fdin[PIPE_RD], STDIN_FILENO) == -1)
	{
		std::cerr << "syscalls forks failed!" << std::endl;
		exit(-1);
	}
	id = fork();
	if (id == 0)
	{
		if (dup2(fdout[PIPE_WR], STDOUT_FILENO) == -1)
		{
			std::cerr << "syscalls forks failed!" << std::endl;
			exit(-1);
		}
		close(fdin[PIPE_RD]);
		close(fdin[PIPE_WR]);
		execve(args[0], args, env);
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

int	run_less(char **env, int *fd)
{
	char *args[2] = {(char *)"/bin/less", 0};
	if (dup2(fd[PIPE_RD], STDIN_FILENO) == -1)
	{
		std::cerr << "syscalls forks failed!" << std::endl;
		exit(-1);
	}
	//std::string s;
	//s.resize(1000);
	//read(STDIN_FILENO, &s[0], 1000);
	//std::cerr << "string.." <<  s << std::endl;
	pid_t id = fork();
	if (id == 0)
	{
		execve(args[0], args, env);

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


int	display_page(std::string &towrite, char **env)
{
	int fd_groff[2];
	int fd_less[2];


	if (pipe(fd_groff) != 0 || pipe(fd_less) != 0)
	{
		std::cerr << "syscalls pipe failed!" << std::endl;
		exit(-1);		
	}
	run_groff(towrite, env, fd_groff, fd_less);
	run_less(env, fd_less);

	return (0);
}