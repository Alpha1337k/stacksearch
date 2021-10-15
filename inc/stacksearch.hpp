#ifndef STACKSEARCH_HPP
#define STACKSEARCH_HPP

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../rapidjson-1.1.0/include/rapidjson/document.h"
#include "../rapidjson-1.1.0/include/rapidjson/writer.h"
#include "../rapidjson-1.1.0/include/rapidjson/stringbuffer.h"
#include <ctime>


#define PIPE_WR 1
#define PIPE_RD 0

class Query
{
private:
	struct answer
	{
		int upvotes;
		bool		is_accepted;
		std::string response;
		std::string name;
	};
	

	std::vector<std::string> tags;
	std::string link;
	std::string title;
	std::string question;
	std::vector<answer> answers;

	std::string sanitizeInput(std::string s);
public:
	Query(/* args */);
	Query(rapidjson::Value::Object o);
	~Query();
	void		ParseQuestionMeta(rapidjson::Value::Object o);
	void		ParseAnswers(rapidjson::Value::Object o);
	std::string Create();
};


int	display_page(std::string &towrite, char **env);
std::string getQuery(std::string param, char **env);
void test();
#endif