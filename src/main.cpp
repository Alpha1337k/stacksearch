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

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: stacksearch [OPTION] QUESTION ...\n" <<
		"try 'stacksearch --help for more information." << std::endl;
		return 1;
	}
	std::string api_rv;
	try
	{
		api_rv = getQuery(argv[1]);
		if (api_rv.length() == 0)
			throw std::invalid_argument(ERROR_START + "curl failed");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}

	rapidjson::Document d;
	d.Parse(api_rv.c_str());

	if (d.HasMember("error_id"))
	{
		std::cout << ERROR_START + "api fail: " << d["error_message"].GetString() << std::endl;
	}
	else if (d["items"].GetArray().Empty())
	{
		std::cout << ERROR_START + "no questions found for '" << argv[1] << "'." << std::endl;
	}
	else if (d["quota_remaining"].GetInt() == 0)
	{
		std::cout << ERROR_START + "error: daily quota filled." << std::endl;
	}
	else
	{
		for (size_t i = 0; i < d["items"].GetArray().Size(); i++)
		{
			Query a(d["items"][i].GetObject());
			std::string page = a.Create();
			display_page(page);
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