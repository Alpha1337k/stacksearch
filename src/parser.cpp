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
	question	= sanitizeInput(o["body_markdown"].GetString());
	for (size_t i = 0; i < o["answers"].GetArray().Size(); i++)
	{
		answer a;
		a.name = o["answers"][i]["owner"]["display_name"].GetString();
		a.response = sanitizeInput(o["answers"][i]["body_markdown"].GetString());
		a.upvotes = o["answers"][i]["score"].GetInt();
		a.is_accepted = o["answers"][i]["is_accepted"].GetBool();
		answers.push_back(a);
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
	/* ghettoass quote parsing and such */

	findAndReplaceAll(s, "&#39;", "'");
	findAndReplaceAll(s, "&quot;", "\"");
	findAndReplaceAll(s, "&lt;", "<");
	findAndReplaceAll(s, "&gt;", ">");
	findAndReplaceAll(s, "&le;", "<=");
	findAndReplaceAll(s, "&ge;", ">=");
	findAndReplaceAll(s, "&ne;", "!=");
	findAndReplaceAll(s, "&eq;", "==");



	// findAndReplaceAll(s, "\n\n", "");
	//  // i want color but i doenst work..
	// findAndReplaceAll(s, "<code>", "\n.I ");
	// findAndReplaceAll(s, "</code>", "\n");
	// findAndReplaceAll(s, "<p>", "");
	// findAndReplaceAll(s, "</p>", "\n");

	// findAndReplaceAll(s, "</a>", "");

	// /* list */
	// findAndReplaceAll(s, "<ul>", "");
	// findAndReplaceAll(s, "</ul>", "");
	// findAndReplaceAll(s, "<li>", "- ");
	// findAndReplaceAll(s, "</li>", "\n");

	// /* pre */
	// findAndReplaceAll(s, "<pre>", "\n.B ");
	// findAndReplaceAll(s, "</pre>", "\n");

	// findAndReplaceAll(s, "<em>", "\n.B ");
	// findAndReplaceAll(s, "</em>", "\n");

	// findAndReplaceAll(s, "<strong>", "\n.B ");
	// findAndReplaceAll(s, "</strong>", "\n");

	// findAndReplaceAll(s, "<blockquote>", "\n_______________________________________________________________________\n.RS 1\n");
	// findAndReplaceAll(s, "</blockquote>",".RE 1\n_______________________________________________________________________\n");

	return s;
}

//void	Query::ParseAnswers(rapidjson::Value::Object o)
//{
//	question	= sanitizeInput(o["body"].GetString());
//	title		= o["title"].GetString();

//	for (size_t i = 0; i < o["answers"].GetArray().Size(); i++)
//	{
//		answer a;
//		a.name = o["answers"][i]["owner"]["display_name"].GetString();
//		a.response = sanitizeInput(o["answers"][i]["body"].GetString());
//		a.upvotes = o["answers"][i]["score"].GetInt();

//		answers.push_back(a);
//	}
	
//}