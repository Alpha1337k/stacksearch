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
	
	rapidjson::Document d;
	d.Parse(getQuestions("").c_str());


	for (size_t i = 0; i < d["items"].GetArray().Size(); i++)
	{
		Query a(d["items"][0].GetObject());
		rapidjson::Document answersDom;
		answersDom.Parse(getAnswers("").c_str());
		a.ParseAnswers(answersDom["items"][0].GetObject());

		std::string page = a.Create();

		std::cout << std::time(0) << std::endl;
		//std::cerr << page << std::endl;

		display_page(page, env);

		std::cout << std::time(0) << std::endl;

		std::cout << "Press 'Q' to quit, 'C' to proceed to next entry" << std::endl;

		break;
	}
}