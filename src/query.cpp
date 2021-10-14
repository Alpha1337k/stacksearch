#include <stacksearch.hpp>

std::string Query::Create()
{
	std::string rval;

	rval += ".TH STACKSEARCH 1 Alpha1337k\n";
	rval += ".SH " + title + "\n";
	rval += question;
	rval += "\n.SH ANSWERS\n\n";

	if (answers.size() == 0)
		rval += ".SS No one has solved this yet!\n";
	else
	{
		for (size_t i = 0; i < answers.size(); i++)
		{
			rval += ".SS [" + std::to_string(answers[i].upvotes) + "] " + answers[i].name + "\n";
			rval += answers[i].response + "\n"; 
		}
	}

	rval += ".SH REFERENCE\n" + link + "\n";

	return rval;
}

			Query::Query()
{
	tags = 0;
	link = "https://stackoverflow.com/questions/29433422/how-to-get-a-list-of-questions-from-stackoverflow-api-based-on-search-query";
	title = "How to get a list of questions from stackoverflow API based on search query?";
	question = "I am interested in the getting a list of the question based on a tag or a search query. I will give you an example. \n\n So If I use the search keyword as \"ipv4\", it should give me a big list of questions related to ipv4. All I want to do is get the questions (title) as a list or an array so that I can do some processing on it.";
	answer a;

	a.response = "You can get this information utilizing the questions/ route. In this call, you will pass the tag(s) you are interested in to the tagged parameter (separated by a semicolon (;)).\n";
	a.upvotes = -1;
	a.name = "Jeff";
	answers.push_back(a);
}

			Query::~Query()
{

}