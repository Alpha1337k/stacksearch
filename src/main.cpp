#include <stacksearch.hpp>

int main(int argc, char **argv, char **env)
{
	if (argc < 2)
	{
		std::cout << "Usage: stacksearch [OPTION] QUESTION ...\n" <<
		"try 'stacksearch --help for more information." << std::endl;
		return 1;
	}
	(void)argv;
	Query a;

	std::string page = a.Create();

	//std::cout << page << std::endl;

	display_page(page, env);
}