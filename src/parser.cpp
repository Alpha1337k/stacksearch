#include <stacksearch.hpp>

void		Query::ParseQuestionMeta(rapidjson::Value::Object o)
{
	link = o["link"].GetString();
	title = o["title"].GetString();
	for (size_t i = 0; i < o["tags"].GetArray().Size(); i++)
	{
		tags.push_back(o["tags"][i].GetString());
	}	
}

		Query::Query(rapidjson::Value::Object o)
{
	link = o["link"].GetString();
	title = o["title"].GetString();
	for (size_t i = 0; i < o["tags"].GetArray().Size(); i++)
	{
		tags.push_back(o["tags"][i].GetString());
	}
}

void		findAndReplaceAll(std::string &s, std::string tofind, std::string toreplace)
{
	size_t pos;
	while ((pos =s.find(tofind)) != std::string::npos)
	{
		s.replace(pos, tofind.length(), toreplace);
	}
}

std::string	Query::sanitizeInput(std::string s)
{
	findAndReplaceAll(s, "<code>", "\e[01;31m");
	findAndReplaceAll(s, "</code>", "\e[0m");

	return s;
}

void	Query::ParseAnswers(rapidjson::Value::Object o)
{
	question	= o["body"].GetString();
	title		= o["title"].GetString();

	for (size_t i = 0; i < 1; i++)
	{
		answer a;
		a.name = o["answers"][i]["owner"]["display_name"].GetString();
		a.response = sanitizeInput(o["answers"][i]["body"].GetString());
		a.upvotes = o["answers"][i]["score"].GetInt();

		answers.push_back(a);
	}
	
}