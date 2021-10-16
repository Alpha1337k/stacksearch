#include <stacksearch.hpp>
#include <fstream>
#include <string>

std::string	getQuestions(std::string tags)
{
	(void)tags;
	std::ifstream jfile("question.json");
	std::string js;
	std::string tmp;

	if (jfile.is_open() == false)
		return "";

	while (std::getline(jfile, tmp))
	{
		js += tmp;
	}

	return js;
}

std::string	getAnswers(std::string tags)
{
	(void)tags;
	std::ifstream jfile("answers.json");
	std::string js;
	std::string tmp;

	if (jfile.is_open() == false)
		return "";

	while (std::getline(jfile, tmp))
	{
		js += tmp;
	}

	return js;
}

int main(int argc, char **argv, char **env)
{
	if (argc < 2)
	{
		std::cout << "Usage: stacksearch [OPTION] QUESTION ...\n" <<
		"try 'stacksearch --help for more information." << std::endl;
		return 1;
	}
	(void)argv;
	
	std::string api_rv = getQuery(argv[1], env);

	rapidjson::Document d;
	d.Parse(api_rv.c_str());

	if (d["items"].GetArray().Empty())
	{
		std::cout << "stacksearch: error: no questions found for '" << argv[1] << "'." << std::endl;
	}
	else if (d["quota_remaining"].GetInt() == 0)
	{
		std::cout << "stacksearch: error: daily quota filled." << std::endl;
	}
	else
	{
		for (size_t i = 0; i < d["items"].GetArray().Size(); i++)
		{
			Query a(d["items"][i].GetObject());
			std::string page = a.Create();
			display_page(page, env);
			char c = ' ';

			if (i + 1 == d["items"].GetArray().Size())
				break;
			if (i == 0)
				std::cout << "Press 'Q' to quit, 'C' to proceed to next entry" << std::endl;
			system("stty raw");
			std::cin >> c;
			system("stty cooked");
			std::cout << '\010';
			if (c == 'Q' || c == 'q')
				break;
		}
	}
	return (0);
}