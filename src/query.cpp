#include <stacksearch.hpp>

std::string Query::Create()
{
	std::string rval;

	std::string trunc_title = title.substr(0, 40) + (title.length() > 20 ? "..." : "");
	rval += ".TH STACKSEARCH 1 \"06-08-2001\" Stacksearch \"" + trunc_title + "\" \n";
	rval += ".SH " + title + "\n";
	rval += question;
	rval += "\n.SH ANSWERS\n";

	if (answers.size() == 0)
		rval += ".SS No one has solved this yet!\nBe the first one!\n";
	else
	{
		for (size_t i = 0; i < answers.size(); i++)
		{
			rval += ".SS [" + std::to_string(answers[i].upvotes) + "] " + answers[i].name + "\n";
			rval += answers[i].response + "\n"; 
		}
	}
	rval += ".SH TAGS\n";
	for (size_t i = 0; i < tags.size(); i++)
	{
		rval += tags[i];
		if (i + 1 != tags.size())
			rval += ", ";
	}
	

	rval += "\n.SH REFERENCE\n.UR " + link + "\n.I Link\n.UE . \n";

	return rval;
}

			Query::Query()
{
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