#ifndef STACKSEARCH_HPP
#define STACKSEARCH_HPP

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define PIPE_WR 1
#define PIPE_RD 0

class Query
{
private:
	struct answer
	{
		int upvotes;
		std::string response;
		std::string name;
	};
	

	std::string *tags;
	std::string link;
	std::string title;
	std::string question;
	std::vector<answer> answers;

public:
	Query(/* args */);
	~Query();
	std::string Create();
};


int	display_page(std::string &towrite, char **env);

#endif