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
		pos += toreplace.length();
		if (s.find_first_not_of(' ', pos) != pos)
		{
			s.replace(pos, s.find_first_not_of(' ', pos) - pos, "");
		}
	}
}

std::string	Query::sanitizeInput(std::string s)
{
	findAndReplaceAll(s, "\n\n", "");
	 // i want color but i doenst work..
	findAndReplaceAll(s, "<code>", "\n.I ");
	findAndReplaceAll(s, "</code>", "\n");
	findAndReplaceAll(s, "<p>", "");
	findAndReplaceAll(s, "</p>", "\n");

	findAndReplaceAll(s, "</a>", "");

	/* list */
	findAndReplaceAll(s, "<ul>", "");
	findAndReplaceAll(s, "</ul>", "");
	findAndReplaceAll(s, "<li>", "- ");
	findAndReplaceAll(s, "</li>", "\n");

	/* pre */
	findAndReplaceAll(s, "<pre>", ".SM");
	findAndReplaceAll(s, "</pre>", "\n");	


	return s;
}

void	Query::ParseAnswers(rapidjson::Value::Object o)
{
	question	= sanitizeInput(o["body"].GetString());
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