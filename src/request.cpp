#include <stacksearch.hpp>

/*
	Url created on https://api.stackexchange.com/docs/advanced-search
*/
std::string getQuery(std::string param)
{
	std::string url = "https://api.stackexchange.com/2.3/search/advanced?pagesize=10&order=desc&sort=votes&accepted=True&body=" + param +
	"&tagged=c&site=stackoverflow&filter=W0YDoPIiQCPY-e";
	findAndReplaceAll(url, " ", "%20");
	char *args[] = {(char *)"curl", (char *)url.c_str(), (char *)"--compressed", (char *)"-k", 0};
	pid_t id;
	std::string rval;
	int	fd[2];

	if (pipe(fd) == -1)
		return ("");
	id = fork();
	if (id == 0)
	{

		if (dup2(fd[PIPE_WR], STDOUT_FILENO) == -1)
			exit(-1);
		close(fd[PIPE_RD]);
		close(fd[PIPE_WR]);
		close(2);
		execvp(args[0], args);
		exit(-2);	
	}
	else
	{
		int ret = 0;
		std::string s;

		close(fd[PIPE_WR]);
		do
		{
			s.resize(1000);
			ret = read(fd[PIPE_RD], &s[0], 1000);
			if (ret > 0)
			{
				s.resize(ret);
				rval += s;
			}
		} while (ret > 0);
		close(fd[PIPE_RD]);
		int status = 0;
		waitpid(id, &status, 0);

		if (WEXITSTATUS(status) == -2)
			throw std::invalid_argument(ERROR_START + "curl failed");
	}
	return rval;
}